#include "console_renderer.h"

#include <unordered_map>
#include <sstream>
#define NOMINMAX
#include <windows.h>

static std::unordered_map<tile_content, char> tile_to_character_map = {
	{ tile_content::apple,      '@' },
	{ tile_content::empty,      ' ' },
	{ tile_content::snake_body, 'o' },
	{ tile_content::snake_head, 'O' },
	{ tile_content::wall,       '#' },
};


console_renderer::console_renderer(const board& state) : console{ GetStdHandle(STD_OUTPUT_HANDLE) }
{
	console_size.X = state.width() + 1;
	console_size.Y = state.height() + 3;

	// resize window to fit
	SMALL_RECT rect{ 0, 0, console_size.X, console_size.Y };
	SetConsoleWindowInfo(console, true, &rect);

	// hide cursor
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(console, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(console, &cursor);
}

void console_renderer::draw(const board& state, int score)
{
	DWORD written;

	for(auto row = 0; row < state.height(); ++row)
	{
		for(auto col = 0; col < state.width(); ++col)
		{
			const auto pos = position{ col, row };
			const auto tile = state.tile(pos);
			WriteConsoleOutputCharacterA(console, &tile_to_character_map[tile], 1, COORD{ short(col), short(row) }, &written);
		}
	}

	auto canvas = std::stringstream{};
	canvas << "Current score: " << score;
	auto output = canvas.str();

	const auto score_pos = COORD{ 0, console_size.Y - 1 };

	WriteConsoleOutputCharacterA(console, output.data(), output.size(), score_pos, &written);
}

void console_renderer::game_over()
{
	DWORD written;
	auto game_over = std::string("GAME OVER");

	for(auto x = 0; x < console_size.X; ++x)
	{
		for(auto y = 0; y < console_size.Y; ++y)
		{
			WriteConsoleOutputCharacterA(console, " ", 1, COORD{ short(x), short(y) }, &written);
		}
	}
	const auto score_pos = COORD{ short(console_size.X - game_over.size()) / 2, console_size.Y / 2 };

	WriteConsoleOutputCharacterA(console, game_over.data(), game_over.size(), score_pos, &written);
}