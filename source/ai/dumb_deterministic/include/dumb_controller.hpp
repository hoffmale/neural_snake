#pragma once

#include "simulation.h"

class dumb_deterministic_ai : public simulation
{
public:
	dumb_deterministic_ai() = default;

protected:
	direction next_move() override;
};