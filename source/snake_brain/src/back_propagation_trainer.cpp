#include "back_propagation_trainer.hpp"

back_propagation_trainer::back_propagation_trainer(::network& net): network_trainer{ net } {}

void back_propagation_trainer::train_mini_batch(const std::vector<sample>& training_samples)
{

	for(auto&& sample : training_samples)
	{
		auto&& [activations, inputs] = network.layer_results(sample.input);
		auto derived_sample_error = derived_error(sample.output, inputs.back());

		update_weights(
			network,
			activations,
			inputs,
			derived_sample_error,
			learning_rate());
	}
}

double back_propagation_trainer::verify(const std::vector<sample>& test_samples)
{
	auto total_error = 0.0;

	for(auto&& sample : test_samples)
	{
		total_error += error(sample.output, network.output(sample.input));
	}

	return total_error;
}

double back_propagation_trainer::error(
	const std::vector<double>& expected_output,
	const std::vector<double>& actual_output)
{
	auto total_error = 0.0;

	for(auto i = 0u; i < expected_output.size(); ++i)
	{
		const auto diff = expected_output[i] - actual_output[i];
		total_error += diff * diff;
	}

	return total_error * 0.5;
}

std::vector<double> back_propagation_trainer::derived_error(
	const std::vector<double>& expected_output,
	const std::vector<double>& actual_output)
{
	auto derived_sample_errors = std::vector<double>{};

	for(auto i = 0u; i < expected_output.size(); ++i)
	{
		derived_sample_errors.push_back(actual_output[i] - expected_output[i]);
	}

	return derived_sample_errors;
}

void back_propagation_trainer::update_weights(
	::network& net,
	const std::vector<std::vector<double>>& activations,
	const std::vector<std::vector<double>>& inputs,
	const std::vector<double>& derived_error,
	double learning_rate) const
{
	auto new_deltas = std::vector<double>{};
	auto deltas = derived_error;

	for(auto&& layer : net.reverse_layers())
	{
		new_deltas.resize(layer.inputs(), 0.0);

		for(auto&& neuron : layer.neurons())
		{
			auto derived_activation_times_delta = functions::re_lu.derivation(
				                                      activations[layer.index()][neuron.index()]) * deltas[neuron.
				                                      index()];

			neuron.bias() -= learning_rate * derived_activation_times_delta;
			for(auto&& weight : neuron.weights())
			{
				new_deltas[weight.index()] += weight.value() * derived_activation_times_delta;

				const auto adjustment = learning_rate * inputs[layer.index()][weight.index()] * derived_activation_times_delta;
				weight.value() -= adjustment;
			}
		}

		deltas = std::move(new_deltas);
	}
}
