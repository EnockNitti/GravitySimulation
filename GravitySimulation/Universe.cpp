#include "main.h"

void Universe::addPlanet(Planet* planet)
{
	planets.push_back(planet);
}

/*******************************************************************/

void Universe::update()
{
	planets[0]->updateVelocityInit(planets);

	// Update acceleration
	double dDeltaVMax = 0;
	for (;; )
	{
		double dDeltaV = updateAccs(planets);
		break;
#if 1
		if (dDeltaV > DELTAVMAX) {
			dTimeStep = dTimeStep / 4;

			for (int i = 0; i < iNPlanets; i++)
			{
				planets[i]->acceleration.Zero();
				dDeltaVMax = 0;
				planets[i]->velocity / 2.0;
			}
			printf("TimeStep %e\n", dTimeStep);
			continue;			// retry with a shorter timestep
		}
		else if (dDeltaV < DELTAVMIN && dTimeStep < TIMESTEP) {
			dTimeStep = dTimeStep * 4;

			for (int i = 0; i < iNPlanets; i++)
			{
				planets[i]->velocity * 2.0;
			}
			printf("TimeStep %e\n", dTimeStep);
			continue;			// retry with a longer timestep
		}

		if (dDeltaV > dDeltaVMax) dDeltaVMax = dDeltaV;
		break;
#endif
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
		Vector TempMomentum = TotMomentum;			// "#¤%& :(			V * m
		Vector VelocityAdjust = TempMomentum * dMyMassQ / dTotalMass;	//  V * m / m
		planet->velocity -= VelocityAdjust;
	}
}

