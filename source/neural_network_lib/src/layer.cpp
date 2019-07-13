#include "layer.hpp"

neuron_iterator::neuron_iterator()
	: data{ nullptr },
	  current_offset{ 0u },
	  max_offset{ 0u },
	  input_size{ 0u } {}

neuron_iterator& neuron_iterator::operator++()
{
	++current_offset;
	return *this;
}

neuron_iterator neuron_iterator::operator++(int)
{
	const auto copy = *this;
	++*this;
	return copy;
}

neuron_iterator::reference neuron_iterator::operator*() const
{
	return neuron{ data + current_offset * neuron::size(input_size), current_offset, input_size };
}

bool neuron_iterator::operator==(neuron_iterator other) const
{
	if(other.data == nullptr)
	{
		return data == nullptr || current_offset == max_offset;
	}

	if(data == nullptr)
	{
		return other.current_offset == other.max_offset;
	}

	return data == other.data && current_offset == other.current_offset && max_offset == other.max_offset && input_size
	       == other.input_size;
}

bool neuron_iterator::operator!=(neuron_iterator other) const { return !(*this == other); }

neuron_iterator::neuron_iterator(double* data, size_t input_size, size_t neuron_count)
	: data{ data },
	  current_offset{ 0u },
	  max_offset{ neuron_count },
	  input_size{ input_size } {}

layer::layer(double* data, size_t input_size, size_t neuron_count, size_t index)
	: data{ data }
	, input_size{ input_size }
	, neuron_count{ neuron_count }
	, layer_index{ index }
{
}

size_t layer::inputs() const { return input_size; }

range<neuron_iterator> layer::neurons() const
{
	return range{ neuron_iterator{ data, input_size, neuron_count }, neuron_iterator{} };
}
