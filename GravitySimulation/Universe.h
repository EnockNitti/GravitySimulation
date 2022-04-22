#pragma once

class Universe
{
public:
	void addPlanet(Planet* planet);
	void update();
	void MomentumAdjust();
	std::vector<Planet*> planets;

private:
};