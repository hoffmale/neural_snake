#include "simulation.h"
#include <random>

constexpr static auto initial_snake_length = 3;

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

	set_tile(snake_head, tile_content::snake_head);

	for(auto i = initial_snake_length; i > 1; --i)
	{
		auto body_part_pos = position{ snake_head.x - i + 1, snake_head.y };
		set_tile(body_part_pos, tile_content::snake_body);
		snake_body_parts.push(body_part_pos);
	}

	create_apple();
}

const std::vector<std::vector<tile_content>>& simulation::field() const
{
	return board;
}

void simulation::set_tile(position pos, tile_content tile)
{
	board[pos.y][pos.x] = tile;
}

tile_content simulation::get_tile(position pos) const
{
	return board[pos.y][pos.x];
}

void simulation::create_apple()
{
	static auto engine = std::mt19937{std::random_device{}()};
	const auto distribution = std::uniform_int_distribution<int>(0, int(board.size() * board.front().size() - 1));

	do {
		const auto index = distribution(engine);
		apple = position{ index / int(board.size()), index % int(board.size()) };
	} while (get_tile(apple) != tile_content::empty);

	set_tile(apple, tile_content::apple);
}

void simulation::move_snake(direction dir)
{
	set_tile(snake_head, tile_content::snake_body);
	snake_body_parts.push(snake_head);

	snake_head = next_snake_head(dir);
	set_tile(snake_head, tile_content::snake_head);

	if (snake_head != apple) {
		set_tile(snake_body_parts.front(), tile_content::empty);
		snake_body_parts.pop();
	}

}

void simulation::check_collision(direction dir)
{
	switch (get_tile(next_snake_head(dir)))
	{
	case tile_content::wall:
	case tile_content::snake_body:
		running = false;
		return;
	case tile_content::apple:
		game_score += 100;
		break;
	default:
		break;
	}
}

position simulation::next_snake_head(direction dir)
{
	auto next_snake_head = snake_head;
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

	return next_snake_head;
}

int simulation::score() const
{
	return game_score;
}

void simulation::move(direction dir)
{
	check_collision(dir);

	if (!running) return;

	move_snake(dir);

	if (snake_head == apple) create_apple();
}