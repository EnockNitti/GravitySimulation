#include "main.h"

void Universe::addPlanet(Planet* planet)
{
	planets.push_back(planet);
}

void Universe::update()
{
	planets[0]->updateVelocityInit(planets);

	// Update acceleration
	double dDeltaVMax = 0;
	for (int i = 0; i < iNPlanets-1; i++)
	{
		double dDeltaV = planets[i]->updateAccs(planets, i);
		if (dDeltaV > DELTAVMAX) {
			i = -1;	// Restart with new TIME_STEP
			dTimeStep = dTimeStep / 4;

			printf("%e\n", dTimeStep);
			for (int i = 0; i < iNPlanets; i++)
			{
				planets[i]->acceleration.Zero();
				dDeltaVMax = 0;
				planets[i]->velocity / 2.0;
			}
		}
		else if( dDeltaV < DELTAVMIN && dTimeStep < TIMESTEP ) {
			i = -1;	// Restart with new TIME_STEP
			dTimeStep = dTimeStep * 4;

			printf("%e\n", dTimeStep);
			for (int i = 0; i < iNPlanets; i++)
			{
				planets[i]->acceleration.Zero();
				dDeltaVMax = 0;
				planets[i]->velocity * 2.0;
			}
		}

		if (dDeltaV > dDeltaVMax) dDeltaVMax = dDeltaV;
	}

#if 0
	// Check speed
	static double dHighSpeed = 0;
	static int iPlanet = -1;
	for (int i = 0; i < iNPlanets; i++)
	{
		double dSpeed = sqrt(planets[i]->velocity.x * planets[i]->velocity.x + planets[i]->velocity.y * planets[i]->velocity.y);
		if (dSpeed * 0.99 > dHighSpeed) {
			dHighSpeed = dSpeed;
			iPlanet = i;
//			printf("%d %g\n", iPlanet, dHighSpeed);
		}
	}
#endif

	// Velocity And Position
	for (int i = 0; i < iNPlanets; i++)
	{
		planets[i]->updateVelocityAndPosition();
//		planets[i]->updatePosition();
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

