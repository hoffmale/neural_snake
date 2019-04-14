#include "network.h"
#include <random>
#include <assert.h>



namespace snn
{
	network::network(Settings const& settings)
		: num_inputs(settings.num_inputs)
		, num_hidden(settings.num_hidden)
		, num_outputs(settings.num_outputs)
	{
		assert(settings.num_inputs > 0 && settings.num_outputs > 0 && settings.num_hidden > 0);
		initialize_network();
		load_weights();
	}

	network::network(Settings const& settings, std::vector<double> const& weights)
		: num_inputs(settings.num_inputs)
		, num_hidden(settings.num_hidden)
		, num_outputs(settings.num_outputs)
	{
		assert(settings.num_inputs > 0 && settings.num_outputs > 0 && settings.num_hidden > 0);
		initialize_network();
		load_weights(weights);
	}

	void network::initialize_network()
	{
		const int total_inputs = num_inputs + 1;
		const int total_hidden = num_hidden + 1;

		input_neurons.resize(total_inputs);
		hidden_neurons.resize(total_hidden);
		output_neurons.resize(num_outputs);
		clamped_outputs.resize(num_outputs);

		memset(input_neurons.data(), 0, input_neurons.size() * sizeof(double));
		memset(hidden_neurons.data(), 0, hidden_neurons.size() * sizeof(double));
		memset(output_neurons.data(), 0, output_neurons.size() * sizeof(double));
		memset(clamped_outputs.data(), 0, clamped_outputs.size() * sizeof(int));

		// Set bias values
		input_neurons.back() = -1.0;
		hidden_neurons.back() = -1.0;

		// Create storage and layer weights
		int const num_input_hidden_weights = total_inputs * total_hidden;
		int const num_output_hidden_weights = total_hidden * num_outputs;
		input_hidden_weights.resize(num_input_hidden_weights);
		output_hidden_weights.resize(num_output_hidden_weights);
	}

	void network::initialize_weights()
	{
		std::random_device rd;
		std::mt19937 generator(rd());

		double const distribution_range_half_width = (2.4 / num_inputs);
		double const standard_deviation = distribution_range_half_width * 2 / 6;
		std::normal_distribution<> normal_dist(0, standard_deviation);

		// Set weights to normally distributed random values between [-2.4 / numInputs, 2.4 / numInputs]
		for (int input_index = 0; input_index <= num_inputs; input_index++)
		{
			for (int hidden_index = 0; hidden_index < num_hidden; hidden_index++)
			{
				int const weight_index = get_input_hidden_weight_index(input_index, hidden_index);
				double const weight = normal_dist(generator);
				input_hidden_weights[weight_index] = weight;
			}
		}

		for (int hidden_index = 0; hidden_index <= num_hidden; hidden_index++)
		{
			for (int output_index = 0; output_index < num_outputs; output_index++)
			{
				int const weight_index = get_hidden_output_weight_index(hidden_index, output_index);
				double const weight = normal_dist(generator);
				output_hidden_weights[weight_index] = weight;
			}
		}
	}

	void network::load_weights(std::vector<double> const& weights)
	{
		int const num_input_hidden_weights = num_inputs * num_hidden;
		int const num_output_hidden_weights = num_hidden * num_outputs;

		int weight_index = 0;
		for (auto input_hidden_index = 0; input_hidden_index < num_input_hidden_weights; input_hidden_index++)
		{
			input_hidden_weights[input_hidden_index] = weights[weight_index];
			weight_index++;
		}

		for (auto output_hidden_index = 0; output_hidden_index < num_output_hidden_weights; output_hidden_index++)
		{
			input_hidden_weights[output_hidden_index] = weights[weight_index];
			weight_index++;
		}
	}

	std::vector<int> const& network::evaluate(std::vector<double> const& input)
	{
		assert(input.size() == num_inputs);
		assert(input_neurons.back() == -1 && hidden_neurons.back() == -1.0);

		// Set input values
		memcpy(input_neurons.data(), input.data(), input.size() * sizeof(double));

		// Update hidden neurons
		for (int hidden_index = 0; hidden_index < num_hidden; hidden_index++)
		{
			hidden_neurons[hidden_index] = 0;

			// Get weighted sum of pattern and bias neuron
			for (int input_index = 0; input_index <= num_inputs; input_index++)
			{
				int const weight_index = get_input_hidden_weight_index(input_index, hidden_index);
				hidden_neurons[hidden_index] += input_neurons[input_index] * input_hidden_weights[weight_index];
			}

			// Apply activation function
			hidden_neurons[hidden_index] = sigmoid_activation_function(hidden_neurons[hidden_index]);
		}

		// Calculate output values - include bias neuron
		for (int output_index = 0; output_index < num_outputs; output_index++)
		{
			output_neurons[output_index] = 0;

			// Get weighted sum of pattern and bias neuron
			for (int hidden_index = 0; hidden_index <= num_hidden; hidden_index++)
			{
				int const weight_index = get_hidden_output_weight_index(hidden_index, output_index);
				output_neurons[output_index] += hidden_neurons[hidden_index] * output_hidden_weights[weight_index];
			}

			// Apply activation function and clamp the result
			output_neurons[output_index] = sigmoid_activation_function(output_neurons[output_index]);
			clamped_outputs[output_index] = clamp_output_value(output_neurons[output_index]);
		}

		return clamped_outputs;
	}
}