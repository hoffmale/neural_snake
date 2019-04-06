#include "simulation.h"

simulation::simulation(int width, int height)
	: board(height, std::vector<tile_content>(width, tile_content::empty)),
	  apple{ 1, 1 },
	  snake_head{width/2, height/2},
	  game_score{ 0 }
{
	for(auto& tile : board.front()) tile = tile_content::wall;
	for(auto& tile : board.back()) tile = tile_content::wall;

	for(auto& row : board)
	{
		row.front() = tile_content::wall;
		row.back() = tile_content::wall;
	}

	board[apple.y][apple.x] = tile_content::apple;
	board[snake_head.y][snake_head.x] = tile_content::snake_head;
	snake_body_parts.push(position{ snake_head.x - 2, snake_head.y });
	snake_body_parts.push(position{ snake_head.x - 1, snake_head.y });
	board[snake_head.y][snake_head.x - 2] = tile_content::snake_body;
	board[snake_head.y][snake_head.x - 1] = tile_content::snake_body;
}

const std::vector<std::vector<tile_content>>& simulation::field() const
{
	return board;
}

int simulation::score() const
{
	return game_score;
}

void simulation::move(direction dir)
{
	auto old_snake_head = snake_head;
	snake_body_parts.push(old_snake_head);
	board[old_snake_head.y][old_snake_head.x] = tile_content::snake_body;
	board[snake_body_parts.front().y][snake_body_parts.front().x] = tile_content::empty;
	snake_body_parts.pop();
	switch (dir)
	{
	case direction::up:
		snake_head.y--;
		break;
	case direction::down:
		snake_head.y++;
		break;
	case direction::left:
		snake_head.x--;
		break;
	case direction::right:
		snake_head.x++;
		break;
	}
	board[snake_head.y][snake_head.x] = tile_content::snake_head;
}