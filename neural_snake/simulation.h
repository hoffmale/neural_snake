#pragma once
#include <vector>
#include <queue>
#include "tile_content.h"
#include "direction.h"

struct position
{
	int x;
	int y;

	bool operator==(position other) const { return x == other.x && y == other.y; }
	bool operator!=(position other) const { return !(*this == other); }
};

class simulation
{
	std::vector<std::vector<tile_content>> board;
	std::queue<position> snake_body_parts;
	position apple;
	position snake_head;
	int game_score;
	bool running = true;

public:
	simulation(int width, int height);

	void move(direction dir);

	bool is_running() const { return running; }
	int score() const;
	const std::vector<std::vector<tile_content>>& field() const;

private:
	void set_tile(position pos, tile_content tile);
	tile_content get_tile(position pos) const;

	void create_apple();
	void move_snake(direction dir);
	void check_collision(direction dir);

	position next_snake_head(direction dir);
};