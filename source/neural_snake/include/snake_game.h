#pragma once
#include "renderer.h"
#include "simulation.h"
#include <chrono>

class snake_game
{
	simulation* game_state;
	renderer* view;
	std::chrono::milliseconds time_step = std::chrono::milliseconds{ 300 };

public:
	snake_game(simulation* game_state, renderer* view);

	void run() const;
	std::chrono::milliseconds delay() const;
	void delay(std::chrono::milliseconds new_delay);
};
