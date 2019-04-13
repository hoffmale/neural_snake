#include "snake_brain.h"

double snake_brain::discount_factor(int time_steps)
{
	return std::pow(0.9, time_steps);
}

double snake_brain::learning_rate()
{
	return 0.1;
}

double snake_brain::reward(const board& state, direction action)
{
	auto snake_heads = state.positions(tile_content::snake_head);
	auto my_head = *snake_heads.begin();

	switch(action)
	{
	case direction::up:
		--my_head.y;
		break;
	case direction::down:
		++my_head.y;
		break;
	case direction::left:
		--my_head.x;
		break;
	case direction::right:
		++my_head.x;
		break;
	}

	my_head = state.wrap(my_head);

	const auto next_tile = state.tile(my_head);
	switch(next_tile)
	{
	case tile_content::empty:
		return -1.0;
	case tile_content::snake_head:
	case tile_content::wall:
	case tile_content::snake_body:
		return -100.0;
	case tile_content::apple:
		return 1000.0;
	}
	return 0.0;
}
