#include "main.h"

void Universe::addPlanet(Planet* planet)
{
	planets.push_back(planet);
}

/*******************************************************************/

void Universe::update()
{
//	planets[0]->updateVelocityInit(planets);

	int iNPlanets = planets.size();
	for (int i = 0; i < iNPlanets; i++)
		planets[i]->acceleration.Zero();	// All accelerations to 0

	// Update acceleration
	double dDeltaVMax = 0;
	for ( int i = 0; i < iNPlanets; i++ )
	{
		if( planets[i]->iNr >= 100) continue;
		double dDeltaV = planets[i]->updateAccs(i, planets);
	}

	// Upppdate Velocity And Position
	for (int i = 0; i < iNPlanets; i++)
	{
		planets[i]->updateVelocityAndPosition();
	}
}

void Universe::MomentumAdjust()
{
	double dTotalMass = 0;
	double dMyMassQ = 0;
	Vector TotMomentum(0.0, 0.0);

	for (auto& planet : planets)
	{
		TotMomentum += planet->Momentum;		// V * m
		dTotalMass += planet->mass;				// m
	}

	for (auto& planet : planets) {
		dMyMassQ = planet->mass / dTotalMass;			
		Vector VelocityAdjust = TotMomentum * dMyMassQ / dTotalMass;	//  V * m / m
		planet->velocity -= VelocityAdjust;
	}
}

