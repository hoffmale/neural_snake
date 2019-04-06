#pragma once
#include "controller.h"
#include "simulation.h"
#include "renderer.h"

class snake_game
{
private:
	controller& control;
	simulation& model;
	renderer& view;

public:
	snake_game(controller& c, simulation& s, renderer& r) : control{ c }, model{ s }, view{ r } {}

	void run();
};
