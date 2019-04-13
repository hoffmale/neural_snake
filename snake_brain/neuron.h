#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <iostream>

double dot_product(const std::vector<double>& a, const std::vector<double>& b)
{
	double result = 0.0;

	// assume a.size() == b.size()
	for(auto i = 0; i < a.size(); ++i)
	{
		result += a[i] * b[i];
	}

	return result;
}

namespace functions
{
	struct function
	{
		virtual ~function() = default;
		virtual double calculate(double input) = 0;
		virtual double gradient(double value) = 0;
		virtual double calculate(double input, const std::vector<double>& neuron_inputs, const std::vector<double>& weights) = 0;
	};

	class arc_tan;
	class arc_max;
	class sigmoid;
	class soft_max;
	class re_lu;

	struct identity : function
	{
		double calculate(double input) override
		{
			return input;
		}

		double calculate(double input, const std::vector<double>& neuron_inputs, const std::vector<double>& weights) override
		{
			const auto result = dot_product(neuron_inputs, weights);
			return result;
		}

		double gradient(double value) override
		{
			return 1.0;
		}
	};

}

enum class function_types : int {
	identity,
};

inline static auto function_map = std::unordered_map<function_types, std::unique_ptr<functions::function>>{};

void initialize_function_map() {
	function_map.insert({ function_types::identity, std::make_unique<functions::identity>() });
}

struct neuron
{
	std::vector<double> input_weights;
	double last_activation;
	double threshold;

	function_types activation_func;
	function_types output_func;

	double output(std::vector<double> inputs)
	{
		last_activation = function_map[activation_func]->calculate(last_activation, inputs, input_weights);
		if (last_activation < threshold) return 0.0;

		return function_map[output_func]->calculate(last_activation);
	}
};

struct neural_layer
{
	std::vector<neuron> neurons;

public:
	std::vector<double> calculate(std::vector<double> inputs)
	{
		auto outputs = std::vector<double>{};

		std::transform(std::begin(neurons), std::end(neurons), std::back_inserter(outputs), [&](auto&& neuron) { return neuron.output(inputs); });

		return outputs;
	}
};

struct neural_network
{
	std::vector<neural_layer> layers;

	std::vector<double> outputs(std::vector<double> inputs)
	{
		for(auto layer : layers)
		{
			inputs = layer.calculate(inputs);
		}

		return inputs;
	}
};

class trainer
{
	neural_network& nn;

	std::vector<std::vector<double>> inputs;
	std::vector<std::vector<double>> expected_outputs;


};

inline void test_nn()
{
	initialize_function_map();

	auto nn = neural_network{ {
		neural_layer{
			{
				neuron{
					{ 0.5, 0.5 },
					0.0,
					0.0,
					function_types::identity,
					function_types::identity
				},
				neuron{
					{ 1.0, 0.0 },
					0.0,
					0.0,
					function_types::identity,
					function_types::identity
				},
			}
		},
	} };

	auto inputs = std::vector<double>{ 1.0, 0.0 };

	auto outputs = nn.outputs(inputs);

	std::cout << "{ " << outputs[0] << ", " << outputs[1] << " }\n";
}