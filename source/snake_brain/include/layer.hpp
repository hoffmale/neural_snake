#pragma once

#include <vector>
#include "neuron.hpp"
#include "functions.hpp"

class layer;

class neuron_iterator
{
	double* data;
	size_t current_offset;
	size_t max_offset;
	size_t input_size;

public:
	friend class layer;

	using value_type = neuron;
	using reference = neuron;
	using pointer = void;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;

	neuron_iterator();

	neuron_iterator& operator++();
	neuron_iterator operator++(int);

	reference operator*() const;

	bool operator==(neuron_iterator other) const;
	bool operator!=(neuron_iterator other) const;

private:
	neuron_iterator(double* data, size_t input_size, size_t neuron_count);
};

class layer
{
	double* data;
	size_t input_size;
	size_t neuron_count;
	size_t layer_index;

public:
	constexpr static size_t size(size_t input_size, size_t neuron_count) { return neuron_count * neuron::size(input_size); }

	layer(double* data, size_t input_size, size_t neuron_count, size_t index);

	size_t inputs() const;
	range<neuron_iterator> neurons() const;
	size_t index() const { return layer_index; }

	template<typename Iterator>
	std::vector<double> activate(Iterator iter) const
	{
		auto activations = std::vector<double>{};

		for(auto&& neuron : neurons())
		{
			activations.push_back(neuron.activate(iter));
		}

		return activations;
	}
};
