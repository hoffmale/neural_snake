#include "dumb_nn_ai.hpp"

dumb_nn_ai::dumb_nn_ai() : brain{ network::create({8, 32, 32, 4 }) }
{
	
}

direction dumb_nn_ai::next_move()
{
	auto state = current_state();

	auto head = *state.positions(tile_content::snake_head).begin();

	auto input = std::vector<double>{};

	auto count = 0.0;
	auto apple_right = 0.0;
	auto snake_right = 0.0;
	for(auto tile = state.wrap(head.right()); tile != head; tile = state.wrap(tile.right()))
	{
		count += 1.0;

		if(state.tile(tile) == tile_content::snake_body || state.tile(tile) == tile_content::snake_head)
		{
			snake_right = count;
			break;
		}

		if(state.tile(tile) == tile_content::apple)
		{
			apple_right = count;
			break;
		}
	}

	input.push_back(apple_right);
	input.push_back(snake_right);

	// ...

	auto result = brain.output(input);

	auto max_res = std::max_element(result.begin(), result.end());
	return (direction)std::distance(result.begin(), max_res);
}
