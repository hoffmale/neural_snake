#include "neuron.hpp"
#include <random>
#include "math.hpp"

/*void neuron::randomize()
{
	static auto engine = std::mt19937{ std::random_device()() };
	static auto distribution = std::uniform_real_distribution<double>(0.0, 1.0);

	bias_value = distribution(engine);

	for(auto& weight : weight_values)
	{
		weight = distribution(engine);
	}
}*/

weight_iterator& weight_iterator::operator++()
{
	++current_offset;
	return *this;
}

weight_iterator weight_iterator::operator++(int)
{
	const auto copy = *this;
	++*this;
	return copy;
}

weight_iterator::reference_type weight_iterator::operator*() const
{
	return weight{ data, current_offset };
}

bool weight_iterator::operator==(weight_iterator other) const
{
	if(other.data == nullptr)
	{
		return data == nullptr || current_offset == max_offset;
	}

	if(data == nullptr)
	{
		return other.current_offset == other.max_offset;
	}

	return data == other.data && current_offset == other.current_offset && max_offset == other.max_offset;
}

bool weight_iterator::operator!=(weight_iterator other) const
{
	return !(*this == other);
}

weight_iterator::weight_iterator(double* first, double* last)
	: data{ first },
	  current_offset{ 0u },
	  max_offset{ size_t(last - first) } {}

neuron::neuron(double* data, size_t offset, size_t input_size)
	: data{ data }
	, weight_count{ input_size }
	, offset{ offset } {}

size_t neuron::index() const { return offset; }

range<weight_iterator> neuron::weights() const
{
	return range{ weight_iterator{ data, data + weight_count }, weight_iterator{} };
}

double& neuron::bias() const { return data[weight_count]; }
