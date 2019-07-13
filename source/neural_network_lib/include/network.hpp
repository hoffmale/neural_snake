#pragma once
#include <initializer_list>
#include <utility>
#include <vector>
#include "layer.hpp"

class network;

class layer_iterator
{
	double* data;
	size_t current_layer;
	size_t offset;
	std::vector<size_t> layer_sizes;

public:
	friend class network;

	using value_type = layer;
	using reference = layer;
	using pointer = void;
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;

	layer_iterator();

	layer_iterator& operator++();
	layer_iterator operator++(int);
	layer_iterator& operator--();
	layer_iterator operator--(int);

	reference operator*() const;

	bool operator==(layer_iterator other) const;
	bool operator!=(layer_iterator other) const;

private:
	layer_iterator(double* data, std::vector<size_t> layer_sizes);
	layer_iterator(double* data, std::vector<size_t> layer_sizes, size_t offset);
};

class network
{
	std::vector<double> weights_and_biases;
	std::vector<size_t> layer_sizes;

public:
	static network create(std::initializer_list<size_t> dimensions);
	static network from_file(std::string filepath);

	size_t size() const;

	range<layer_iterator> layers();
	range<std::reverse_iterator<layer_iterator>> reverse_layers();

	std::vector<double> output(std::vector<double> input);

	std::tuple<std::vector<std::vector<double>>, std::vector<std::vector<double>>> layer_results(
		const std::vector<double>& input);

	void randomize();

	void save_to_file(std::string filename);
};
