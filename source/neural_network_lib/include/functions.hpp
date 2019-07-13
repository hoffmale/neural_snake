#pragma once
#include <vector>

class function
{
public:
	virtual double calculate(double input) const = 0;
	virtual double derivation(double input) const = 0;

	virtual ~function() = default;
};

class re_lu_function : public function
{
	double leak_factor;
public:
	re_lu_function(double leak_factor = 0.0);

	double calculate(double input) const override;
	double derivation(double input) const override;
};

namespace functions
{
	inline static const re_lu_function re_lu{ 0.0 };
	inline static const re_lu_function leaky_re_lu{ 0.01 };
}

std::vector<double> apply(const function* func, const std::vector<double>& input);
std::vector<double> apply_derivation(const function* func, const std::vector<double>& input);
