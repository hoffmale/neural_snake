#include "snake_game.h"

void snake_game::run()
{
	// TODO: update model using controller input
	view.draw();
	model.move(direction::up);
	view.draw();
}
