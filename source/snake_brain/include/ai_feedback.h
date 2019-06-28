#pragma once
#include "renderer.h"
#include <memory>

class ai_feedback : public renderer
{
	std::unique_ptr<renderer> real_view;

public:
	ai_feedback(std::unique_ptr<renderer> real_view);

	void draw(const board& state, int score) override;
	void game_over() override;
};
