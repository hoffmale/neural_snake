#pragma once
#include "position.h"
#include "board.h"

#include <queue>
#include "direction.h"

class snake
{
	board& state;
	position head;
	std::queue<position> body_parts;

public:
	snake(board& state, position start, int length);

	void move(direction dir);
	bool can_move(direction dir) const noexcept;

private:
	position next_head(direction dir) const noexcept;
};
