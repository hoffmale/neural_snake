#pragma once
#include <vector>


namespace snn
{
	enum class ActivationFunctionType
	{
		Sigmoid
	};

	class network
	{
		friend class trainer;

		double sigmoid_activation_function(double x)
		{
			return 1.0 / (1.0 + std::exp(-x));
		}

		int clamp_output_value(double x)
		{
			if (x < 0.1)
				return 0;
			else if (x > 0.9)
				return 1;
			else
				return -1;
		}

	public:
		struct Settings
		{
			int num_inputs;
			int num_hidden;
			int num_outputs;
		};

		network(Settings const& settings);
		network(Settings const& settings, std::vector<double> const& weights);

		std::vector<int> const& evaluate(std::vector<double> const& input);

		std::vector<double> const& get_input_hidden_weights() const { return input_hidden_weights; }
		std::vector<double> const& get_output_hidden_weights() const { return output_hidden_weights; }


	private:
		void initialize_network();
		void initialize_weights();
		void load_weights(std::vector<double> const& weights);

		int get_input_hidden_weight_index(int input_index, int hidden_index) const { return input_index * num_hidden + hidden_index; }
		int get_hidden_output_weight_index(int hidden_index, int output_index) const { return hidden_index * num_outputs + output_index; }

		int num_inputs;
		int num_hidden;
		int num_outputs;

		std::vector<double> input_neurons;
		std::vector<double> hidden_neurons;
		std::vector<double> output_neurons;

		std::vector<int> clamped_outputs;

		std::vector<double> input_hidden_weights;
		std::vector<double> output_hidden_weights;
	};
}