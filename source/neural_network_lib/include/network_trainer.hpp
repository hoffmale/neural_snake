#pragma once
#include "network.hpp"
#include "sample.hpp"
#include <iostream>

class network_trainer
{
	double rate;

protected:
	network& network;

public:
	network_trainer(::network& network);
	virtual ~network_trainer() = default;

	double learning_rate() const;
	void learning_rate(double new_rate);

	virtual void train_mini_batch(const std::vector<sample>& training_samples) = 0;
	virtual double verify(const std::vector<sample>& test_sample) = 0;

	void train(
		const std::vector<sample>& training_samples,
		const std::vector<sample>& verification_samples,
		size_t epochs);
};
