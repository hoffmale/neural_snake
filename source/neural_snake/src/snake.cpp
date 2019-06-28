#include "snake.h"
#include <iterator>

snake::snake(board& state, position start, int length)
	: state{ state }
	, head{ start }
{
	state.tile(head, tile_content::snake_head);

	for(int i = length; i > 1; --i)
	{
		auto body_part_pos = position{ head.x - i + 1, head.y };
		state.tile(body_part_pos, tile_content::snake_body);
		body_parts.push(body_part_pos);
	}
}

void snake::move(direction dir)
{
	state.tile(head, tile_content::snake_body);
	body_parts.push(head);

	head = next_head(dir);
	const auto ate_apple = state.tile(head) == tile_content::apple;
	state.tile(head, tile_content::snake_head);

	if(!ate_apple)
	{
		state.tile(body_parts.front(), tile_content::empty);
		body_parts.pop();
	}
}

bool snake::can_move(direction dir) const noexcept
{
	const auto next_pos = next_head(dir);

	return state.tile(next_pos) == tile_content::empty || state.tile(next_pos) == tile_content::apple;
}

position snake::next_head(direction dir) const noexcept
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
