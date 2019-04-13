#pragma once
#include "ai_controller.h"
#include "ai_feedback.h"
#include "snake.h"
#include "neuron.h"

class snake_brain
{
	ai_controller controller;
	ai_feedback feedback;

	std::vector<neuron> input_neurons;
	std::vector<neuron> hidden_neurons;
	std::vector<neuron> output_neurons;

	std::vector<std::vector<double>> weights;
public:
	double discount_factor(int time_steps);
	double learning_rate();
	double reward(const board& state, direction action);
	direction next_move();
};
