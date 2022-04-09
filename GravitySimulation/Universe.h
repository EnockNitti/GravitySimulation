#pragma once

#include "Planet.h"
#include <vector>

class Universe
{
public:
	void addPlanet(Planet* planet);
	void update();
	void render(SDL_Renderer* renderer);
	void MomentumAdjust();
	std::vector<Planet*> planets;


private:
};