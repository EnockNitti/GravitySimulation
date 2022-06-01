#include "main.h"

void Universe::addPlanet(Planet* planet)
{
	planets.push_back(planet);
}

/*******************************************************************/

void Universe::update()
{
	
	for (int i = 0; i < planets.size(); i++) {
		planets[i]->acceleration.Zero();	// All accelerations to 0
		if (planets[i]->iNr >= 1000 ) {		// Marked for deletion
			planets.erase(planets.begin() + i);
			printf("Collision. Planets merged\n");
		}
	}

	// Update acceleration
	for ( int i = 0; i < planets.size(); i++ )
	{
		if( planets[i]->iNr >= 100) continue;
		planets[i]->updateAccs(i, planets);
	}

	// Upppdate Velocity And Position
	for (int i = 0; i < planets.size(); i++)
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

