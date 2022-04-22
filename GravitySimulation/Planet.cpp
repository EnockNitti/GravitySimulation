#include "main.h"

extern Game* game;


Planet::Planet(double mass, Vector position, Vector velocity, int iNr, double dL2Dist )
{
	this->radius = sqrt(cbrt(mass / DENSITY / PI / 3));
	if (this->radius < 1) this->radius = 1;

	this->acceleration = Vector();
	this->mass = mass;
	this->position = position;
	this->velocity = velocity * sqrt(TIME_STEP);
	this->Momentum = velocity * mass;
	this->iNr = iNr;
	this->dL2Dist = dL2Dist;

	const char* q;
	SDL_Surface* tempSurface;

	if (iNr < 100 )
		tempSurface = IMG_Load("planet.png");
	else
		tempSurface = IMG_Load("Marker.png");
	q = SDL_GetError();

	this->texture = SDL_CreateTextureFromSurface( game->renderer, tempSurface);
	q = SDL_GetError();

	SDL_FreeSurface(tempSurface);
}

void Planet::updateVelocity(std::vector<Planet*>& others)
{
	static long unsigned int luiLastIterations = 0;

	this->acceleration = Vector();

	for (auto& other : others)
	{
		if (this->iNr == 100 && other->iNr == 1) // If marker and a planet L4
		{
			this->position = other->position;
			this->position.Rotate(pi2 * -60 / 360);
			continue;
		}

		if (this->iNr == 101 && other->iNr == 1) // If marker and a planet L2
		{
			this->position = other->position;
			this->position.Extend(this->dL2Dist);
			continue;
		}

		//cant collide with itself
		if (other == this || this->iNr >= 100 || other->iNr >= 100 ) continue;

		Vector posV = other->position - this->position;
		double len = posV.Lenght();
		Vector mag = posV / len;

		double distance2 = (( position.x - other->position.x ) * (position.x - other->position.x) + 
			(position.y - other->position.y * (position.y - other->position.y )));
//		double distance2 = sqrt(pow(position.x - other->position.x, 2) + pow(position.y - other->position.y, 2));
//		if (distance2 < 0.4)
//			continue;

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

		if (iNr == 1 && other->iNr == 0 ) {				// if log planet ( going CV )
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
		if (iNr == 1 && other->iNr == 4 ) {
			static double  dLastX = -1;
			static double  dLastY = -1;
			luiIterations++;

			if( /*dLastX * position.x <= 0.0 || */ dLastY * position.y <= 0.0 )
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
		if (iNr == 1 && other->iNr == 2 ) {		// Planet and L4
			static double  dLastX = 1e10;
			luiIterations++;


			if( dLastX < 0 && position.x >= 0 )
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

		static double dForceMax = 0;
//		double force = this->mass * other->mass * G / pow(len, 2);
		double force = this->mass * other->mass * G / ( len * len );
#if 0
		if (force / 2.0 > dForceMax)
//			if (force > dForceMax)
		{
			dForceMax = force;
			printf("F:%.9g\n", dForceMax);
		}
#endif
		if (force > 1000000.0)
			force = 1000000.0;
		this->acceleration += (mag * force / this->mass) * TIME_STEP;
	}
		this->velocity += this->acceleration;

		luiIterations++;

}

void Planet::updatePosition()
{
	this->position += this->velocity;
}

// Render one planet
void Planet::render(SDL_Renderer* renderer)
{
	this->destRect.w = this->destRect.h = (int)this->radius * 2;

	this->destRect.x = (int)(this->position.x - this->radius + WIDTH / 2);
	this->destRect.y = HIGHT - (int)( this->position.y + this->radius + HIGHT / 2 );			// Y upp

	SDL_RenderCopy(renderer, this->texture, 0, &destRect);
}
