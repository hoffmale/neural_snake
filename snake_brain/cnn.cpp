#include "Matrix.h"
#include "linear_algebra.h"
#include "cnn.h"
#include "Utility.h"
#include <assert.h>
#include <cmath>
#include <random>


CNN::CNN(Image_Shape input_dim, Image_Shape kernel_size, Image_Shape pool_size, int hidden_layer_nodes,
	int output_dim)
{
	/* 
	   As in Python's Tensor flow library we use this function to initialize the weight matrix and kernel matrix
	   Since there is only one hidden_layer, there will be two weight matrices - one between the pool layer and one 
	   that maps the hidden layer to output.
	   Also there is only one convolution layer, so only one kernel.
	 */
	assert(input_dim.num_rows > kernel_size.num_rows && input_dim.num_colums > kernel_size.num_colums);
	assert(input_dim.num_rows - kernel_size.num_rows + 1 > pool_size.num_rows &&
		input_dim.num_colums - kernel_size.num_colums + 1 > pool_size.num_colums);

	kernel = Matrix(kernel_size.num_rows, kernel_size.num_colums);

	pool_window = pool_size;

	int x = ((input_dim.num_rows - kernel_size.num_rows + 1) / pool_size.num_rows);
	int y = ((input_dim.num_colums - kernel_size.num_colums + 1) / pool_size.num_colums);

	Matrix W0((x*y) + 1, hidden_layer_nodes);
	this->weights.emplace_back(W0);
	Matrix W1(hidden_layer_nodes + 1, output_dim);
	this->weights.emplace_back(W1);
}

int CNN::forward_propagate(Matrix& input, std::vector<Matrix>& conv_activations, std::vector<std::vector<double>>& activations)
{
	// We provide the inputs to the convolutional nn and outputs each dense layer which is then appended
	// as a vector to activations. The output of the convolution layer is appended to conv_activations.
	assert(weights.size() == 2);
	Matrix conv = Matrix(input.get_rows() - kernel.get_rows() + 1, input.get_columns() - kernel.get_columns() + 1);

	for (auto i = 0; i < conv.get_rows(); ++i)
	{
		for (auto j = 0; j < conv.get_columns(); ++j)
		{
			conv.set(i, j, np::multiply(kernel, input, i, j));
		}
	}
	conv = np::apply_function(conv, fns::relu);

	auto x = conv.get_rows() / pool_window.num_rows;
	auto y = conv.get_columns() / pool_window.num_colums;

	Matrix pool(conv.get_rows(), conv.get_columns());
	std::vector<double> flatten_pool;

	// Apply convolution to conv matrix
	int xptr = 0, yptr = 0;
	Image_Shape max_index({ 0, 0 });
	for (int i = 0; i < x; ++i)
	{
		xptr = (i * pool_window.num_rows);
		for (int j = 0; j < y; ++j)
		{
			yptr = (j * pool_window.num_colums);
			double max = np::maximum(conv, xptr, yptr, pool_window, max_index);
			flatten_pool.push_back(max);
			pool.set(max_index.num_rows, max_index.num_colums, 1);
		}
	}

	conv_activations[0] = pool;

	// Append some bias constant to input and output of every layer
	flatten_pool.push_back(1);

	// Apply relu to hidden function
	Matrix W0 = np::transpose(weights[0]);
	std::vector<double> hidden = np::dot(W0, flatten_pool, 0);
	hidden = np::apply_function(hidden, fns::relu);
	hidden.push_back(1);

	activations[0] = flatten_pool;

	// Apply softmax to get output layer
	Matrix W1 = np::transpose(weights[1]);
	std::vector<double> output = np::dot(W1, hidden, 0);
	output = np::apply_function(output, fns::softmax);
	output = np::normalize(output);

	activations[1] = hidden;
	activations[2] = output;

	return 0;
}

int CNN::back_propagate(std::vector<double>& delta_L, std::vector<Matrix>& conv_activations,
	std::vector<std::vector<double>>& activations, Matrix& input, double(*active_fn_der)(double), double learning_rate)
{
	// We compute the deltas of eachg layer
	// delta_L - is the delta of the final layer, computed and passed as an argument
	// activations - the output of each layer after applying the acivation function
	// We assume that all layers have the same activation function except the final layer i.e. relu -> softmax
	// active_fn_der - is the function pointer of the derivative of the activation function
	std::vector<double> delta_h = np::dot(weights[1], delta_L, 0);
	std::vector<double> active = np::apply_function(activations[1], active_fn_der);

	delta_h = np::multiply(delta_h, active);

	std::vector<double> delta_x = np::dot(weights[0], delta_h, 1);

	Matrix delta_conv(conv_activations[0].get_rows(), conv_activations[0].get_columns());

	int counter = 0;
	for (auto r = 0; r < conv_activations[0].get_rows(); ++r)
	{
		for (auto c = 0; c < conv_activations[0].get_columns(); ++c)
		{
			if (conv_activations[0].get(r, c) == 1.0)
			{
				delta_conv.set(r, c, delta_x[counter]);
				++counter;
			}
		}
	}

	// Update weights
	Matrix dW0 = np::dot(activations[0], delta_h, 1);
	Matrix dW1 = np::dot(activations[1], delta_L, 0);
	dW0 = np::multiply(dW0, learning_rate);
	dW1 = np::multiply(dW1, learning_rate);

	weights[0] = np::subtract(weights[0], dW0);
	weights[1] = np::subtract(weights[1], dW1);

	for (auto i = 0; i < kernel.get_rows(); ++i)
	{
		for (auto j = 0; j < kernel.get_columns(); ++j)
		{
			kernel.set(i, j, np::multiply(delta_conv, input, i, j));
		}
	}

	return 0;
}

double CNN::cross_entropy(std::vector<double>& ypred, std::vector<double>& ytrue) 
{
	// Calculate cross entropy loss if the predictions and true values are given
	assert(ypred.size() == ytrue.size());
	std::vector<double> z = np::apply_function(ypred, log);
	z = np::multiply(z, ytrue);
	double error = np::element_sum(z);
	return (-error);
}

int CNN::train(std::vector<Matrix>& X_train, std::vector<std::vector<double>>& Y_train, double learning_rate, int epochs)
{
	// We train the network i.e. update erights such that the error between forward propagation X_train and Y_train is 
	// minimized. We break X_train and Y_train into batches od size batch_size and run the following:
	// forward_propagate -> calculate error (cross entropy) -> back propagate -> update weights

	assert(X_train.size() == Y_train.size());

	int e = 1;
	while (e <= epochs)
	{
		int i = 0;
		double error = 0;
		while (i < X_train.size())
		{
			std::vector<Matrix> conv_activations(2);
			std::vector<std::vector<double>> activations(3);

			forward_propagate(X_train[i], conv_activations, activations);
			error += cross_entropy(activations.back(), Y_train[i]);

			std::vector<double> delta_L = np::subtract(activations.back(), Y_train[i]);
			back_propagate(delta_L, conv_activations, activations, X_train[i], fns::relu_gradient, learning_rate);
			
			i++;
		}
		std::cout << "epoch: " << e << " error: " << (error / X_train.size()) << std::endl;
		e++;
	}
	return 0;
}

double CNN::validate(std::vector<Matrix>& X_test, std::vector<std::vector<double>>& Y_test)
{
	// Calculate the error over the testing set to see how well the model performed
	assert(X_test.size() == Y_test.size());
	int i = 1;
	double error = 0;
	while (i <= X_test.size())
	{
		std::vector<Matrix> conv_activations(2);
		std::vector<std::vector<double>> activations(3);

		forward_propagate(X_test[i], conv_activations, activations);
		error += cross_entropy(activations.back(), Y_test[i]);

		i++;
	}
	std::cout << "error: " << (error / X_test.size()) << std::endl;
	return (error / X_test.size());
}