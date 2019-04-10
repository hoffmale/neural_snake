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


console_renderer::console_renderer(simulation& state) : renderer{ state }, console{ GetStdHandle(STD_OUTPUT_HANDLE) }
{
	console_size.X = state.field().front().size() + 1;
	console_size.Y = state.field().size() + 3;

	// resize window to fit
	SMALL_RECT rect{ 0, 0, console_size.X, console_size.Y };
	SetConsoleWindowInfo(console, true, &rect);

	// hide cursor
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(console, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(console, &cursor);
}

void console_renderer::draw()
{
	short x = 0, y = 0;
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

	auto scorePos = COORD{ 0, console_size.Y - 1 };

	WriteConsoleOutputCharacterA(console, output.data(), output.size(), scorePos, &written);
}

void console_renderer::game_over()
{
	DWORD written;
	auto gameOver = std::string("GAME OVER");

	for(auto x = 0; x < console_size.X; ++x)
	{
		for(auto y = 0; y < console_size.Y; ++y)
		{
			WriteConsoleOutputCharacterA(console, " ", 1, COORD{ short(x), short(y) }, &written);
		}
	}
	auto scorePos = COORD{ short(console_size.X - gameOver.size()) / 2, console_size.Y / 2 };

	WriteConsoleOutputCharacterA(console, gameOver.data(), gameOver.size(), scorePos, &written);
}