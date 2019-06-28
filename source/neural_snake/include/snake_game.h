#pragma once
#include "controller.h"
#include "renderer.h"
#include "board.h"
#include "snake.h"

class snake_game
{
	controller& control;
	renderer& view;

	board& state;
	snake snake;
	position apple{ 1, 1 };
	int game_score;
	bool running = true;

public:
	snake_game(controller& c, board& s, renderer& r);

	void run();

private:
	void tick();
	void create_apple();
};
