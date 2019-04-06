#include "simulation.h"

simulation::simulation(int width, int height)
	: board(height, std::vector<tile_content>(width, tile_content::empty)),
	  apple{ 1, 1 },
	  snake_head{height/2, width/2},
	  game_score{ 0 }
{
	for(auto& tile : board.front()) tile = tile_content::wall;
	for(auto& tile : board.back()) tile = tile_content::wall;

	for(auto& row : board)
	{
		row.front() = tile_content::wall;
		row.back() = tile_content::wall;
	}
}

const std::vector<std::vector<tile_content>>& simulation::field() const
{
	return board;
}

int simulation::score() const
{
	return game_score;
}
