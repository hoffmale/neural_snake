#pragma once

#include "renderer.h"

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
