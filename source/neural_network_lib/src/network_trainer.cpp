#include "network_trainer.hpp"

network_trainer::network_trainer(::network& network)
: rate{ 0.01 }
, network{ network }
{
}

double network_trainer::learning_rate() const
{
	return rate;
}

void network_trainer::learning_rate(double new_rate)
{
	rate = new_rate;
}

void network_trainer::train(
	const std::vector<sample>& training_samples,
	const std::vector<sample>& verification_samples,
	size_t epochs)
{
	for(auto epoch = 0u; epoch < epochs; ++epoch)
	{
		train_mini_batch(training_samples);

		if (epoch % 100 == 0) {
			const auto total_error = verify(verification_samples);
			std::cout << "[Round " << epoch << "] Total error: " << total_error << "\n";
		}
	}
}
