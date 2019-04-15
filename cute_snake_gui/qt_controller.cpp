#include "qt_controller.h"

qt_controller::qt_controller(const qt_controller& other)
	: current_direction{ other.current_direction.load() }
{
}

direction qt_controller::next_move()
{
	return current_direction;
}

void qt_controller::up()
{
	current_direction = direction::up;
}

void qt_controller::down()
{
	current_direction = direction::down;
}

void qt_controller::left()
{
	current_direction = direction::left;
}

void qt_controller::right()
{
	current_direction = direction::right;
}
