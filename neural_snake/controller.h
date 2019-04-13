#pragma once

#include "direction.h"

class controller
{
public:
	controller() = default;
	virtual ~controller() = default;

	virtual direction next_move() = 0;
};
