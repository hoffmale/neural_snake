#pragma once

#include <vector>

template<typename T>
auto dot_product(const std::vector<T>& a, const std::vector<T>& b)
{
	if (a.size() != b.size()) throw std::invalid_argument("vector sizes don't match");

	auto sum = T();

	for(auto i = 0u; i < a.size(); ++i)
	{
		sum += a[i] * b[i];
	}

	return sum;
}

template<typename T, typename Callable>
auto apply(Callable&& func, const std::vector<T>& input)
{
	using out_type = std::invoke_result_t<Callable, T>;

	auto result = std::vector<out_type>{};

	for(auto&& value : input)
	{
		result.push_back(std::forward<Callable>(func)(value));
	}

	return result;
}
