#include "snake_game.h"

#include <thread>
#include <random>

constexpr static auto initial_snake_length = 3;
constexpr static auto apple_score = 100;
constexpr static auto delay = std::chrono::milliseconds{ 300 };

snake_game::snake_game(controller& c, board& s, renderer& r)
	: control{ c }
	, view{ r }
	, state{ s }
	, snake{ state, position{ state.width() / 2, state.height() / 2}, initial_snake_length }
	, game_score{ 0 }
{
	create_apple();
}

void snake_game::run()
{
	while(running)
	{
		view.draw(state, game_score);
		std::this_thread::sleep_for(delay);
		tick();
	}
	
	view.game_over();
}

void snake_game::tick()
{
	const auto dir = control.next_move();

	if (snake.can_move(dir))
	{
		snake.move(dir);

		if (state.tile(apple) == tile_content::snake_head) {
			game_score += apple_score;
			create_apple();
		}
	}
	else
	{
		running = false;
	}
}

void snake_game::create_apple()
{
	static auto engine = std::mt19937{ std::random_device{}() };

	auto empty_tiles = state.positions(tile_content::empty);
	if (empty_tiles.empty())
	{
		running = false;
		return;
	}

	const auto distribution = std::uniform_int_distribution<int>(0, int(empty_tiles.size() - 1));

	apple = *std::next(std::begin(empty_tiles), distribution(engine));
	state.tile(apple, tile_content::apple);
}

