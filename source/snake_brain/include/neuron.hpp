#pragma once
#include <vector>
#include "ranges.hpp"

class neuron;
class weight_iterator;

class weight
{
	double* data;
	size_t offset;

public:
	friend class weight_iterator;

	double& value() const { return data[offset]; }
	size_t index() const { return offset; }

private:
	weight(double* data, size_t index) : data{ data }, offset{ index } {}
};

class weight_iterator
{
	double* data;
	size_t current_offset;
	size_t max_offset;

public:
	friend class neuron;

	using value_type = weight;
	using reference_type = weight;
	using pointer = weight;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;

	weight_iterator() : data{ nullptr }, current_offset{ 0u }, max_offset{ 0u } {}

	weight_iterator& operator++();
	weight_iterator operator++(int);
	reference_type operator*() const;
	bool operator==(weight_iterator other) const;
	bool operator!=(weight_iterator other) const;

private:
	weight_iterator(double* first, double* last);
};

class neuron
{
	double* data;
	size_t offset;
	size_t weight_count;

public:
	constexpr static size_t size(size_t input_size) { return input_size + 1u; }

	neuron(double* data, size_t offset, size_t input_size);

	size_t index() const;
	double& bias() const;
	range<weight_iterator> weights() const;

	template<typename Iterator>
	double activate(Iterator input) const
	{
		auto activation = bias();

		for(auto weight : weights())
		{
			activation += weight.value() * *input++;
		}

		return activation;
	}
};
