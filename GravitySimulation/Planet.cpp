#include "Planet.h"
#include "Game.h"

#include "SDL_image.h"
#include "SDL.h"

#include <Windows.h>


extern Game* game;


Planet::Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer, int iNr)
{
	this->radius = std::cbrt(mass / DENSITY / PI / 3);
	if (this->radius < 1) this->radius = 1;

	this->acceleration = Vector();
	this->mass = mass;
	this->position = position;
	this->velocity = velocity * sqrt(TIME_STEP);
	this->Momentum = velocity * mass;
	this->iNr = iNr;

	const char* q;
	SDL_Surface* tempSurface;

	if (iNr < 100 )
		tempSurface = IMG_Load("planet.png");
	else
		tempSurface = IMG_Load("Marker.png");
	q = SDL_GetError();

	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	q = SDL_GetError();

	printf("%s\n", q );

	SDL_FreeSurface(tempSurface);
	
	printf("d   X:%.9g,  Y:%.9g  %d\n", this->position.x, this->position.x, this->iNr);

}

void Planet::updateVelocity(std::vector<Planet*>& others)
{
	static long unsigned int luiLastIterations = 0;
	static long unsigned int luiIterations = 0;

	this->acceleration = Vector();

	for (auto& other : others)
	{
		printf("b    X:%.9g,  Y:%.9g  %d\n", this->position.x, this->position.x, this->iNr);
		SDL_Delay(1000);

		if( this->iNr >= 100 && other->iNr == 1 ) // If marker and a planet
		{
			this->position = other->position;
			this->position.Rotate(pi2 * -60 / 360);
			continue;
		}

		//cant collide with itself
		if (other == this || this->iNr >= 100 || other->iNr >= 100 ) continue;

		Vector posV = other->position - this->position;
		double distance = posV.Lenght();
		Vector mag = posV / distance;

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
				return;
			}
			else
			{
				other->mass += this->mass;
				other->velocity += this->velocity * this->mass / other->mass;

				others.erase(std::remove(others.begin(), others.end(), this), others.end());
				return;
			}
		}//*/
#endif


#if ELIPTIC
		// For log at aphelion
		static unsigned int uiLast = 0;

		printf("h   X:%.9g,  Y:%.9g, N:%lu, dN:%lu, t:%d\n",
			posV.x, posV.y, luiIterations, luiIterations - luiLastIterations, iNr);

		if (iNr == 1 && other->iNr == 0 ) {				// if log planet ( going CV )
			static long unsigned int luiIterations = 0;
			static double  dLastDistance = 1e10;
			static double  dLastLastDistance = 0;
			unsigned int uiNow = SDL_GetTicks();
			luiIterations++;

			if (distance < dLastDistance && dLastDistance > dLastLastDistance)
			{
				printf("g   X:%.9g,  Y:%.9g, N:%lu, dN:%lu, t:%d, dt:%d\n",
					posV.x, posV.y, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast);
				uiLast = uiNow;
				luiLastIterations = luiIterations;
			}
			dLastLastDistance = dLastDistance;
			dLastDistance = distance;
		}
#endif

#if false
		//  Going CV
		static unsigned int uiLast = 0;

		// For log a When crossing X-Axis when going CV
		if (iNr == 1 && other->iNr == 0) {
			static double  dLastX = 1e10;
			luiIterations++;

			if (dLastX < 0 && posV.x >= 0)
			{
				unsigned int uiNow = SDL_GetTicks();
				printf("X:%.9g,  Y:%.9g, N:%lu, dN:%lu, t:%d, dt:%d\n  X:%.9g,  Y:%.9g\n",
					position.x, position.y, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast,
					other->position.x, other->position.y);
				/*
								printf("X:%.9g,  Y:%.9g, N:%lu, dN:%lu, t:%d, dt:%d\n",
									posV.x, posV.y, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast) ;
				*/
				uiLast = uiNow;
				luiLastIterations = luiIterations;
			}
			dLastX = posV.x;
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
				printf("L4X:%.9g,  L4Y:%.9g, Dist:%.9g N:%lu, dN:%lu, t:%d, dt:%d\n",
					pL4->position.x, pL4->position.y, distance, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast);
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
		double force = this->mass * other->mass * G / pow(distance, 2);
		this->acceleration += (mag * force / this->mass) * TIME_STEP;
	}
		this->velocity += this->acceleration;
}

void Planet::updatePosition()
{
	this->position += this->velocity;
//	SDL_Delay(100);

}

void Planet::render(SDL_Renderer* renderer)
{
	this->destRect.w = this->destRect.h = (int)this->radius * 2;

	this->destRect.x = (int)(this->position.x - this->radius + WIDTH / 2);
	this->destRect.y = HIGHT - (int)( this->position.y - this->radius + HIGHT / 2 );			// Y upp

	if( iNr >= 100 )
		SDL_RenderCopy(renderer, this->texture, 0, &destRect);
	else
		SDL_RenderCopy(renderer, this->texture, 0, &destRect);

//	exit(4);
}
