#include "Utility.h"
#include <cmath>

namespace fns
{
	double relu(double x)
	{
		x > 0 ? x : 0;
	}

	double sigmoid(double x)
	{
		return 1.0 / (1.0 + exp(-x));
	}

	double tan(double x)
	{
		return tanh(x);
	}

	double relu_gradient(double x)
	{
		x > 0 ? 1 : 0.2;
	}

	double sigmoid_gradient(double x)
	{
		return x * (1 - x);
	}

	double tan_gradient(double x)
	{
		return 1 - (x * x);
	}

	double softmax(double x)
	{
		isnan(x) ? 0 : exp(x);
	}
}