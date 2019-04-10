#pragma once

#include "controller.h"

#include <atomic>
#include <thread>

class console_input : public controller
{
	std::atomic<direction> last_direction = direction::right;
	std::atomic<bool> running = true;
	std::thread input_reader;

public:
	console_input();
	virtual ~console_input();

	console_input(console_input&&) = delete;
	console_input(const console_input&) = delete;

	console_input& operator=(console_input&&) = delete;
	console_input& operator=(const console_input&) = delete;

	direction next_move() override;

private:
	void read_input();
};
