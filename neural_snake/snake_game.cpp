#include "snake_game.h"
#include <thread>
#include <random>

constexpr auto delay = std::chrono::milliseconds{ 300 };

void snake_game::run()
{
	view.draw();

	while(model.is_running())
	{
		std::this_thread::sleep_for(delay);
		model.move(control.next_move());
		view.draw();
	}
	
	view.game_over();
}

