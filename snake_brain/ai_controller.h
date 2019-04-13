#pragma once
#include "controller.h"

class ai_controller : public controller
{
public:
	direction next_move() override;
};
