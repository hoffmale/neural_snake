#include "renderer.h"
#include <unordered_map>
#include <sstream>
#include <windows.h>

static std::unordered_map<tile_content, char> tile_to_character_map = {
	{ tile_content::apple,      '@' },
	{ tile_content::empty,      ' ' },
	{ tile_content::snake_body, 'o' },
	{ tile_content::snake_head, 'O' },
	{ tile_content::wall,       '#' },
};


void console_renderer::draw()
{
	short x = 0, y = 0;
	auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written;

	for(auto& row : state.field())
	{
		for(auto tile : row)
		{
			WriteConsoleOutputCharacterA(console, &tile_to_character_map[tile], 1, COORD{ x, y }, &written);
			++x;
		}

		++y;
		x = 0;
	}

	auto canvas = std::stringstream{};
	canvas << "Current score: " << state.score();
	auto output = canvas.str();
	auto scorePos = COORD{ 0, short(state.field().size() + 3) };

	WriteConsoleOutputCharacterA(console, output.data(), output.size(), scorePos, &written);
}

void console_renderer::game_over()
{
	DWORD written;
	auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	auto out = std::stringstream{};
	out << "GAME OVER!";
	auto output = out.str();
	auto scorePos = COORD{ 0, short(state.field().size() + 10) };

	WriteConsoleOutputCharacterA(console, output.data(), output.size(), scorePos, &written);
}