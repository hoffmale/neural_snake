#pragma once
#include "Matrix.h"
#include <random>



struct Image_Shape
{
	int num_rows;
	int num_colums;
};


namespace fns
{
	double relu(double x);
	double sigmoid(double x);
	double tan(double x);
	double relu_gradient(double x);
	double sigmoid_gradient(double x);
	double tan_gradient(double x);
	double softmax(double x);
}

