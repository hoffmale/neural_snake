#include "snake.h"
#include <iterator>

snake::snake(board& state, position start, int length)
	: head{ start }
{
	state.tile(head, tile_content::snake_head);

	for(int i = length; i > 1; --i)
	{
		auto body_part_pos = position{ head.x - i + 1, head.y };
		state.tile(body_part_pos, tile_content::snake_body);
		body_parts.push(body_part_pos);
	}
}

board snake::move(const board& old_state, direction dir)
{
	auto next_state = old_state;

	next_state.tile(head, tile_content::snake_body);
	body_parts.push(head);

	head = next_head(old_state, dir);
	next_state.tile(head, tile_content::snake_head);

	const auto ate_apple = old_state.tile(head) == tile_content::apple;
	if(!ate_apple)
	{
		next_state.tile(body_parts.front(), tile_content::empty);
		body_parts.pop();
	}

	return next_state;
}

bool snake::can_move(const board& state, direction dir) const noexcept
{
	const auto next_pos = next_head(state, dir);

	return state.tile(next_pos) == tile_content::empty || state.tile(next_pos) == tile_content::apple;
}

position snake::next_head(const board& state, direction dir) const noexcept
{
	auto next_snake_head = head;

	switch (dir)
	{
	case direction::up:
		next_snake_head.y--;
		break;
	case direction::down:
		next_snake_head.y++;
		break;
	case direction::left:
		next_snake_head.x--;
		break;
	case direction::right:
		next_snake_head.x++;
		break;
	}

	return state.wrap(next_snake_head);
}
