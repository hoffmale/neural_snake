#pragma once
#include "board.h"

class renderer
{
public:
	virtual ~renderer() = default;

	virtual void draw(const board& state, int score) = 0;
	virtual void game_over() = 0;
};
