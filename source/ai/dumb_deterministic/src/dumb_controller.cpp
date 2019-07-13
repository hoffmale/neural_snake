#include "dumb_controller.hpp"

direction dumb_deterministic_ai::next_move()
{
	auto state = current_state();

	if(int(state.positions(tile_content::snake_body).size()) < 10*state.width())
	{
		auto apple = *state.positions(tile_content::apple).begin();
		auto snake_head = *state.positions(tile_content::snake_head).begin();

		if(apple.x == snake_head.x)
		{
			if (!snake.can_move(state, direction::right)) return direction::down;

			for(auto pos = state.wrap(snake_head.down()); pos != apple; pos = state.wrap(pos.down()))
			{
				if (state.tile(pos) != tile_content::empty) return direction::right;
			}

			return direction::down;
		}
	}

	if (snake.can_move(state, direction::right)) return direction::right;

	return direction::down;
	/*auto snake_heads = state.positions(tile_content::snake_head);
	auto snake_head = *snake_heads.begin();

	auto right_of_head = state.wrap(position{ snake_head.x + 1, snake_head.y });
	if(state.tile(right_of_head) == tile_content::snake_body || state.tile(right_of_head) == tile_content::wall)
	{
		return direction::down;
	}

	//if (state.positions(tile_content::snake_body).size() < state.width()) {
		auto apples = state.positions(tile_content::apple);
		auto apple = *apples.begin();

		if(apple.x == snake_head.x)
		{
			auto down_of_apple = state.wrap(position{ apple.x, apple.y + 1 });
			if (state.tile(down_of_apple) == tile_content::snake_body) return direction::right;

			auto down_of_head = state.wrap(position{ snake_head.x, snake_head.y + 1 });
			while(down_of_head != apple)
			{
				if(state.tile(down_of_head) == tile_content::snake_body || state.tile(down_of_head) == tile_content::wall)
				{
					return direction::right;
				}

				++down_of_head.y;
				down_of_head = state.wrap(down_of_head);
			}

			return direction::down;
		}
	//}

	return direction::right;*/
}
