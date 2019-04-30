#pragma once
#include "Matrix.h"
#include "Utility.h"


class CNN
{
public:
	// Since each image is a matrix we will store all these images in a vector
	int train(std::vector<Matrix>& X_train, std::vector<std::vector<double>>& Y_train, double learning_rate, int epochs);
	
	double validate(std::vector<Matrix>& X_test, std::vector<std::vector<double>>& Y_test);

	CNN(Image_Shape input_dim, Image_Shape kernel_size, Image_Shape pool_size, int hidden_layer_nodes, int output_dim);

private:
	std::vector<Matrix> weights;
	Matrix kernel;
	Image_Shape pool_window;
	int forward_propagate(Matrix& input, std::vector<Matrix>& conv_activations, std::vector<std::vector<double>>& activations);




};