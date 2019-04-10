#include <memory>
#include "snake_game.h"
#include <iostream>

int main()
{
	{
		std::unique_ptr<simulation> model = std::make_unique<simulation>(30, 15);
		std::unique_ptr<controller> controller = std::make_unique<console_input>();
		std::unique_ptr<renderer>   view = std::make_unique<console_renderer>(*model);

		snake_game game(*controller, *model, *view);

		game.run();
	}

	std::cin.get();
}
