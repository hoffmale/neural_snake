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
	int xptr, yptr = 0;
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

	// Append some bias constant to input and putput of every layer
	flatten_pool.push_back(1);

	// Apply relu to hidden function
	Matrix W0 = np::transpose(weights[0]);
	std::vector<double> hidden = np::dot(W0, flatten_pool);
	hidden = np::apply_function(hidden, fns::relu);
	hidden.push_back(1);

	activations[0] = flatten_pool;

	// Apply softmax to get output layer
	Matrix W1 = np::transpose(weights[1]);
	std::vector<double> output = np::dot(W1, hidden);
	output = np::apply_function(output, fns::softmax);
	output = np::normalize(output);

	activations[1] = hidden;
	activations[2] = output;

	return 0;
}