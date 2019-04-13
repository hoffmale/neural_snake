#pragma once

#include "renderer.h"

#include <windows.h>

class console_renderer : public renderer
{
	HANDLE console;
	COORD console_size{};

public:
	console_renderer(const board& state);

	void draw(const board& state, int score) override;
	void game_over() override;
};
