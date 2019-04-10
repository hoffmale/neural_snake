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

#include <windows.h>

class console_renderer : public renderer
{
	HANDLE console;
	COORD console_size{};

public:
	console_renderer(simulation& state);

	void draw() override;
	void game_over() override;
};
