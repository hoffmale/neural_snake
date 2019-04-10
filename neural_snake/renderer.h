#pragma once
#include "simulation.h"

class renderer
{
protected:
	const simulation& state;

public:
	renderer(simulation& state) : state{ state } {}
	virtual ~renderer() = default;

	virtual void draw() = 0;
	virtual void game_over() = 0;
};
