#include "console_input.h"
#include <windows.h>

console_input::console_input()
	: input_reader{ [this](){ while (running) read_input(); } }
{
}

console_input::~console_input()
{
	running = false;
	input_reader.join();
}

direction console_input::next_move()
{
	return last_direction;
}

void console_input::read_input()
{
	INPUT_RECORD input;
	auto console = GetStdHandle(STD_INPUT_HANDLE);
	DWORD read;
	ReadConsoleInputA(console, &input, 1, &read);

	if (read == 0 || input.EventType != KEY_EVENT) return;
	if (!input.Event.KeyEvent.bKeyDown) return;

	switch(input.Event.KeyEvent.uChar.AsciiChar)
	{
	case 'w':
		last_direction = direction::up;
		break;
	case 'a':
		last_direction = direction::left;
		break;
	case 's':
		last_direction = direction::down;
		break;
	case 'd':
		last_direction = direction::right;
		break;
	default:
		break;
	}
}

