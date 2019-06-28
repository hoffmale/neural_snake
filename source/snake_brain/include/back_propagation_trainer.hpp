#pragma once

#include "network_trainer.hpp"

class back_propagation_trainer : public network_trainer
{
public:
	back_propagation_trainer(::network& net);

	void train_mini_batch(const std::vector<sample>& training_samples) override;

	double verify(const std::vector<sample>& test_samples) override;

private:
	static double error(const std::vector<double>& expected_output, const std::vector<double>& actual_output);

	static std::vector<double> derived_error(
		const std::vector<double>& expected_output,
		const std::vector<double>& actual_output);

	void update_weights(
		::network& net,
		const std::vector<std::vector<double>>& activations,
		const std::vector<std::vector<double>>& inputs,
		const std::vector<double>& derived_error,
		double learning_rate) const;
};