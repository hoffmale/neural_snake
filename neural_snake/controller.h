#pragma once

#include "direction.h"

class controller
{
public:
	controller() = default;

	virtual direction next_move() = 0;
};
