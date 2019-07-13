#pragma once
#include "position.h"
#include "board.h"

#include <queue>
#include "direction.h"

class snake
{
	position head;
	std::queue<position> body_parts;

public:
	snake(board& state, position start, int length);

	board move(const board& old_state, direction dir);
	bool can_move(const board& state, direction dir) const noexcept;

private:
	position next_head(const board& state, direction dir) const noexcept;
};
