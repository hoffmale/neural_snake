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


}