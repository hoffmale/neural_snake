#pragma once
#include <vector>
#include <queue>
#include "tile_content.h"
#include "direction.h"

struct position
{
	int x;
	int y;
};

class simulation
{
	std::vector<std::vector<tile_content>> board;
	std::queue<position> snake_body_parts;
	position apple;
	position snake_head;
	int game_score;

public:
	simulation(int width, int height);

	//void move(direction dir);

	//bool is_running() const;

	int score() const;

	const std::vector<std::vector<tile_content>>& field() const;
};