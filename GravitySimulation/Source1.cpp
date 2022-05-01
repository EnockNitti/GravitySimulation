// Lite sparad kod


#if 0

//collision
if (sqrt(pow((position.x + radius - other->position.x - other->radius), 2) + pow((position.y + radius - other->position.y - other->radius), 2)) < radius + other->radius)
{
	if (this->mass > other->mass)
	{
		this->mass += other->mass;
		this->velocity += other->velocity * other->mass / this->mass;
		//this->radius = std::cbrt(4 * mass / DENSITY / PI / 3);

		others.erase(std::remove(others.begin(), others.end(), other), others.end());
		continue;
	}
	else
	{
		this->velocity += other->velocity * other->mass / this->mass;
		this->mass += other->mass;
		others.erase(std::remove(others.begin(), others.end(), this), others.end());
		continue;
	}
}//*/
#endif


#if ELIPTIC
	// For log at aphelion
static unsigned int uiLast = 0;

if (iNr == 1 && other->iNr == 0) {				// if log planet ( going CV )
	luiIterations++;
	static double  dLastDistance = 1e10;
	static double  dLastLastDistance = 0;
	unsigned int uiNow = SDL_GetTicks();

	if (distance2 < dLastDistance && dLastDistance > dLastLastDistance)
	{
		printf("g   X:%.9g,  Y:%.9g, N:%lu, dN:%lu, t:%d, dt:%d\n",
			posV.x, posV.y, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast);
		uiLast = uiNow;
		luiLastIterations = luiIterations;
	}
	dLastLastDistance = dLastDistance;
	dLastDistance = distance2;
}
#endif

#if LOGL2
//  Going CV
static unsigned int uiLast = 0;

// For log a When crossing Axis 
if (iNr == 1 && other->iNr == 4) {
	static double  dLastX = -1;
	static double  dLastY = -1;
	luiIterations++;

	if ( /*dLastX * position.x <= 0.0 || */ dLastY * position.y <= 0.0)
	{
		unsigned int uiNow = SDL_GetTicks();
		printf("X:%.9g, Y:%.9g,  Xv:%.9g, Yv:%.9g, N:%lu, dN:%lu, t:%d, dt:%d\n",
			position.x, position.y, velocity.x, velocity.y, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast);

		printf("X:%.9g, Y:%.9g,  Xv:%.9g,  Yv:%.9g\n",
			other->position.x, other->position.y, other->velocity.x, other->velocity.y);
		/*
						printf("X:%.9g,  Y:%.9g, N:%lu, dN:%lu, t:%d, dt:%d\n",
							posV.x, posV.y, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast) ;
		*/
		uiLast = uiNow;
		luiLastIterations = luiIterations;
	}
	dLastX = position.x;
	dLastY = position.y;
}
#endif

#if LOGL4
//  Going CV
static unsigned int uiLast = 0;

// For log of L4 When planet crossing X-Axis when going CV
Planet* pL4 = game->universe.planets[2];			// L4
if (iNr == 1 && other->iNr == 2) {		// Planet and L4
	static double  dLastX = 1e10;
	luiIterations++;


	if (dLastX < 0 && position.x >= 0)
	{
		unsigned int uiNow = SDL_GetTicks();
		printf("L4X:%.9g,  L4Y:%.9g, N:%lu, dN:%lu, t:%d, dt:%d\n",
			pL4->position.x, pL4->position.y, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast);
		//				printf("Y:%.9g\n", position.y);
		uiLast = uiNow;
		luiLastIterations = luiIterations;
	}
	else if (dLastX > 0 && position.x <= 0)
	{
		//				printf("Y:%.9g\n", position.y);
	}
	dLastX = position.x;
}
#endif



#if 0
if (force / 2.0 > dForceMax)
//			if (force > dForceMax)
{
	dForceMax = force;
	printf("F:%.9g\n", dForceMax);
}
#endif

