#pragma once
#include <vector>
#include "tile_content.h"
#include "position.h"
#include <unordered_set>

class board
{
	std::vector<tile_content> board_state;
	int board_width;
	int board_height;

public:
	board(int width = 30, int height = 15);

	int width() const noexcept;
	int height() const noexcept;

	tile_content tile(position pos) const noexcept;
	void tile(position pos, tile_content new_content) noexcept;

	std::unordered_set<position> positions(tile_content content) const;

	position wrap(position pos) const noexcept;

private:
	int calc_index(position pos) const noexcept;
	position calc_position(int index) const noexcept;
};
