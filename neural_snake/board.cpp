#include "board.h"

board::board(int width, int height)
	: board_state(width * height, tile_content::empty)
	, board_width{ width }
	, board_height{ height }
{
}

int board::width() const noexcept
{
	return board_width;
}

int board::height() const noexcept
{
	return board_height;
}

tile_content board::tile(position pos) const noexcept
{
	const auto index = calc_index(pos);

	return board_state[index];
}

void board::tile(position pos, tile_content new_content) noexcept
{
	const auto index = calc_index(pos);

	board_state[index] = new_content;
}

std::unordered_set<position> board::positions(tile_content content) const
{
	auto positions = std::unordered_set<position>{};

	for(auto iter = std::find(std::begin(board_state), std::end(board_state), content);
		iter != std::end(board_state);
		iter = std::find(std::next(iter), std::end(board_state), content))
	{
		positions.insert(calc_position(std::distance(std::begin(board_state), iter)));
	}

	return positions;
}

position board::wrap(position pos) const noexcept
{
	const auto real_y = (pos.y % board_height + board_height) % board_height;
	const auto real_x = (pos.x % board_width + board_width) % board_width;

	return position{ real_x, real_y };
}

int board::calc_index(position pos) const noexcept
{
	const auto real_pos = wrap(pos);

	return real_pos.y * board_width + real_pos.x;
}

position board::calc_position(int index) const noexcept
{
	const auto x = index % board_width;
	const auto y = index / board_width;

	return position{ x, y };
}
