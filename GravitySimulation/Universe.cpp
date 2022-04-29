#include "main.h"

void Universe::addPlanet(Planet* planet)
{
	planets.push_back(planet);
}

void Universe::update()
{
	for (auto& planet : planets)
	{
		planet->updateVelocity(planets);
	}

	for (auto& planet : planets)
	{
		planet->updatePosition();
	}
}


void Universe::MomentumAdjust()
{
	double dTotalMass = 0;
	double dMyMassQ = 0;
	Vector TotMomentum(0.0, 0.0);

	for (auto& planet : planets)
	{
		TotMomentum += planet->Momentum;
		dTotalMass += planet->mass;
	}

	for (auto& planet : planets) {
		dMyMassQ = planet->mass / dTotalMass;
		Vector VelocityAdjust = TotMomentum / (dMyMassQ * dTotalMass);
		planet->velocity -= VelocityAdjust;
	}
}

