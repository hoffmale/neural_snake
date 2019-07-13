#include "simulation.h"
#include <random>

constexpr static auto initial_snake_length = 3;
constexpr static auto apple_score = 100;

simulation::simulation() : snake{state, {state.width() / 2, state.height() / 2}, initial_snake_length}, game_score{ 0 }, can_continue{ true }
{
	create_apple();
}

void simulation::update()
{
	const auto move = next_move();

	std::tie(state, can_continue) = perform_move(state, move);

	if (state.tile(apple) == tile_content::snake_head) {
		game_score += apple_score;
		create_apple();
	}
}

bool simulation::is_running() const
{
	return can_continue;
}

board simulation::current_state() const
{
	return state;
}

int simulation::score() const
{
	return game_score;
}

std::tuple<board, bool> simulation::perform_move(board state, direction move)
{
	if (snake.can_move(state, move))
	{
		state = snake.move(state, move);
		return { state, true };
	}
	else
	{
		return { state, false };
	}
}

void simulation::create_apple()
{
	static auto engine = std::mt19937{ std::random_device{}() };

	auto empty_tiles = state.positions(tile_content::empty);
	if (empty_tiles.empty())
	{
		can_continue = false;
		return;
	}

	const auto distribution = std::uniform_int_distribution<int>(0, int(empty_tiles.size() - 1));

	apple = *std::next(std::begin(empty_tiles), distribution(engine));
	state.tile(apple, tile_content::apple);
}
