#include "functions.hpp"
#include <algorithm>
#include "math.hpp"

re_lu_function::re_lu_function(double leak_factor)
: leak_factor{ leak_factor }
{
}

double re_lu_function::calculate(double input) const
{
	return std::max(leak_factor*input, input);
}

double re_lu_function::derivation(double input) const
{
	return input < 0.0 ? leak_factor : 1.0;
}

std::vector<double> apply(const function* func, const std::vector<double>& input)
{
	auto lambda = [&](auto value) { return func->calculate(value); };
	return apply(lambda, input);
}

std::vector<double> apply_derivation(const function* func, const std::vector<double>& input)
{
	auto lambda = [&](auto value) { return func->derivation(value); };
	return ::apply(lambda, input);
}
