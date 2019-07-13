#pragma once

#include "board.h"
#include "direction.h"
#include "snake.h"

class simulation
{
private:
	board state;
	position apple{ 1, 1 };
	int game_score;
	bool can_continue;

public:
	simulation();
	virtual ~simulation() = default;

	void update();
	bool is_running() const;
	board current_state() const;
	int score() const;

protected:
	std::tuple<board, bool> perform_move(board state, direction move);
	virtual direction next_move() = 0;
	snake snake;

private:
	void create_apple();
};
