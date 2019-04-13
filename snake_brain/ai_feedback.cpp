#include "ai_feedback.h"

ai_feedback::ai_feedback(std::unique_ptr<renderer> real_view)
	: real_view{ std::move(real_view) }
{
}

void ai_feedback::draw(const board& state, int score)
{
	if (real_view) real_view->draw(state, score);
}

void ai_feedback::game_over()
{
	if (real_view) real_view->game_over();
}

