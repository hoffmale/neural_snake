#include "network.hpp"
#include "functions.hpp"
#include <random>
#include <fstream>
#include <iterator>

layer_iterator::layer_iterator()
	: data{ nullptr },
	  current_layer{ 0u },
	  offset{ 0u } {}

layer_iterator& layer_iterator::operator++()
{
	offset += layer::size(layer_sizes[current_layer], layer_sizes[current_layer + 1]);
	++current_layer;

	return *this;
}

layer_iterator layer_iterator::operator++(int)
{
	auto copy = *this;
	++*this;
	return copy;
}

layer_iterator& layer_iterator::operator--()
{
	--current_layer;
	offset -= layer::size(layer_sizes[current_layer], layer_sizes[current_layer + 1]);

	return *this;
}

layer_iterator layer_iterator::operator--(int)
{
	auto copy = *this;
	--*this;
	return copy;
}

layer_iterator::reference layer_iterator::operator*() const
{
	return layer{ data + offset, layer_sizes[current_layer], layer_sizes[current_layer + 1], current_layer };
}

bool layer_iterator::operator==(layer_iterator other) const
{
	if(other.data == nullptr)
	{
		return data == nullptr || current_layer + 1 >= layer_sizes.size();
	}

	if(data == nullptr)
	{
		return other.current_layer + 1 >= other.layer_sizes.size();
	}

	return data == other.data && current_layer == other.current_layer && layer_sizes == other.layer_sizes;
}

bool layer_iterator::operator!=(layer_iterator other) const { return !(*this == other); }

layer_iterator::layer_iterator(double* data, std::vector<size_t> layer_sizes)
	: data{ data },
	  current_layer{ 0u },
	  offset{ 0u },
	  layer_sizes{ std::move(layer_sizes) } {}

layer_iterator::layer_iterator(double* data, std::vector<size_t> layer_sizes, size_t offset)
	: data{ data },
	  current_layer{ layer_sizes.size() - 1 },
	  offset{ offset },
	  layer_sizes{ std::move(layer_sizes) } {}

network network::create(std::initializer_list<size_t> dimensions)
{
	auto net = network{};

	net.layer_sizes = dimensions;
	net.weights_and_biases.resize(net.size(), 0.0);

	return net;
}

network network::from_file(std::string filepath)
{
	auto file = std::fstream{ filepath, std::ios::binary | std::ios::in | std::ios::out };

	network net{};

	size_t num_layers;
	file.read(reinterpret_cast<char*>(&num_layers), sizeof(num_layers));

	net.layer_sizes.resize(num_layers);
	file.read(reinterpret_cast<char*>(net.layer_sizes.data()), num_layers * sizeof(size_t));

	net.weights_and_biases.resize(net.size());
	file.read(reinterpret_cast<char*>(net.weights_and_biases.data()), net.weights_and_biases.size() * sizeof(double));

	return net;
}

size_t network::size() const
{
	auto input_size = layer_sizes.front();
	auto total_size = 0u;

	for(auto neuron_count = std::next(std::begin(layer_sizes)); neuron_count != std::end(layer_sizes); ++neuron_count)
	{
		total_size += layer::size(input_size, *neuron_count);
		input_size = *neuron_count;
	}

	return total_size;
}

range<layer_iterator> network::layers()
{
	return range{ layer_iterator{ weights_and_biases.data(), layer_sizes }, layer_iterator{} };
}

range<std::reverse_iterator<layer_iterator>> network::reverse_layers()
{
	return range{
		std::reverse_iterator<layer_iterator>{
			layer_iterator{ weights_and_biases.data(), layer_sizes, weights_and_biases.size() }
		},
		std::reverse_iterator<layer_iterator>{
			layer_iterator{ weights_and_biases.data(), layer_sizes }
		}
	};
}

std::vector<double> network::output(std::vector<double> input)
{
	auto result = input;

	for(auto&& layer : layers())
	{
		result = ::apply(&functions::leaky_re_lu, layer.activate(result.begin()));
	}

	return result;
}

std::tuple<std::vector<std::vector<double>>, std::vector<std::vector<double>>> network::layer_results(
	const std::vector<double>& input)
{
	auto activations = std::vector<std::vector<double>>{};
	auto inputs = std::vector<std::vector<double>>{};

	inputs.push_back(input);

	for(auto&& layer : layers())
	{
		activations.push_back(layer.activate(inputs.back().begin()));
		inputs.push_back(::apply(&functions::leaky_re_lu, activations.back()));
	}

	return std::make_tuple(activations, inputs);
}

void network::randomize()
{
	static auto engine = std::mt19937{ std::random_device()() };
	static auto dist = std::uniform_real_distribution<double>(0.0, 1.0);

	for (auto&& value : weights_and_biases)
	{
		value = dist(engine);
	}
}

void network::save_to_file(std::string filename)
{
	auto file = std::fstream{ filename, std::ios::binary | std::ios::out };

	auto num_layers = layer_sizes.size();
	file.write(reinterpret_cast<char*>(&num_layers), sizeof(num_layers));
	file.write(reinterpret_cast<char*>(layer_sizes.data()), num_layers * sizeof(size_t));
	file.write(reinterpret_cast<char*>(weights_and_biases.data()), weights_and_biases.size() * sizeof(double));
}

