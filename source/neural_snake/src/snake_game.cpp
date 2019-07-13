#include "snake_game.h"

#include <thread>
#include <random>

constexpr static auto delay = std::chrono::milliseconds{ 300 };

snake_game::snake_game(simulation* game_state, renderer* view) : game_state{ game_state }, view{ view }
{
}

void snake_game::run() const
{
	while(game_state->is_running())
	{
		view->draw(game_state->current_state(), game_state->score());
		std::this_thread::sleep_for(time_step);
		game_state->update();
	}
	
	view->game_over();
}

std::chrono::milliseconds snake_game::delay() const
{
	return time_step;
}

void snake_game::delay(std::chrono::milliseconds new_delay)
{
	time_step = new_delay;
}

