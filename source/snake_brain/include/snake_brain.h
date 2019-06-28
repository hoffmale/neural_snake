#pragma once
#include "ai_controller.h"
#include "ai_feedback.h"
#include "snake.h"

class snake_brain
{
	ai_controller controller;
	ai_feedback feedback;

public:
	double discount_factor(int time_steps);
	double learning_rate();
	double reward(const board& state, direction action);
	direction next_move();
};
