#include "qt_renderer.h"

void qt_renderer::draw(const board& state, int score)
{
	emit render(state, score);
}

void qt_renderer::game_over()
{
	emit finish();
}
