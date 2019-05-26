#include "console_input.h"
#include "console_renderer.h"

#include "snake_game.h"

#include <memory>
#include <iostream>
#include "ai_controller.h"
#include "ai_feedback.h"

int main()
{
	{
		//std::unique_ptr<simulation> model = std::make_unique<simulation>(30, 15);
		auto state = board{ 30, 15 };
		//std::unique_ptr<controller> controller = std::make_unique<console_input>();
		std::unique_ptr<controller> controller = std::make_unique<ai_controller>();
		std::unique_ptr<renderer>   view = std::make_unique<console_renderer>(state);
		std::unique_ptr<renderer> ai_view = std::make_unique<ai_feedback>(std::move(view));

		snake_game game(*controller, state, *ai_view);

		game.run();
	}

	std::cin.get();
}
