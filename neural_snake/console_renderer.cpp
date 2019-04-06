#include "renderer.h"
#include <iostream>
#include <unordered_map>

static std::unordered_map<tile_content, char> tile_to_character_map = {
	{ tile_content::apple,      '@' },
	{ tile_content::empty,      ' ' },
	{ tile_content::snake_body, 'o' },
	{ tile_content::snake_head, 'O' },
	{ tile_content::wall,       '#' },
};


void console_renderer::draw()
{
	for(auto& row : state.field())
	{
		for(auto& tile : row)
		{
			std::cout << tile_to_character_map[tile];
		}

		std::cout << "\n";
	}

	std::cout << "\nCurrent score: " << state.score() << "\n";
}
