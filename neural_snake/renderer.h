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

class console_renderer : public renderer
{
public:
	console_renderer(simulation& state) : renderer{ state } {}

	void draw() override;
	void game_over();
};
