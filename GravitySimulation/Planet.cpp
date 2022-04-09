#include "Planet.h"
#include "Game.h"

#include "SDL_image.h"
#include "SDL.h"

#include <Windows.h>

#define LOGAHELION false
#define LOGXEQ0 false
#define LOGL4 true


extern Game* game;


Planet::Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer, int iNr)
{
	this->radius = std::cbrt( mass / DENSITY / PI / 3);
	if (this->radius < 1) this->radius = 1;

	this->acceleration = Vector();
	this->mass = mass;
	this->position = position;
	this->velocity = velocity * sqrt( TIME_STEP );
	this->Momentum = velocity * mass;
	this->iNr = iNr;


	SDL_Surface* tempSurface = IMG_Load("planet.png");
	const char* q = SDL_GetError();
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	q = SDL_GetError();
	SDL_FreeSurface(tempSurface);
}

void Planet::updateVelocity(std::vector<Planet*>& others)
{
	static long unsigned int luiLastIterations = 0;
	static long unsigned int luiIterations = 0;

	this->acceleration = Vector();

	for (auto& other : others)
	{
		//cant collide with itself
		if (other == this) continue;

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
#if LOGAHELION
		// For log at aphelion
		static unsigned int uiLast = 0;

		if (iNr == 2 && other->iNr == 0 ) {				// if log planet 2 ( going CV )
			static long unsigned int luiIterations = 0;
			static double  dLastDistance = 1e10;
			static double  dLastLastDistance = 0;
			unsigned int uiNow = SDL_GetTicks();
			luiIterations++;

			if (distance < dLastDistance && dLastDistance > dLastLastDistance)
			{
				printf("X:%.9g,  Y:%.9g, N:%lu, dN:%lu, t:%d, dt:%d\n",
					posV.x, posV.y, luiIterations, luiIterations - luiLastIterations, uiNow, uiNow - uiLast);
				uiLast = uiNow;
				luiLastIterations = luiIterations;
			}
			dLastLastDistance = dLastDistance;
			dLastDistance = distance;
		}

#endif
#if LOGXEQ0
		//  Going CV
		static unsigned int uiLast = 0;

		// For log a When crossing X-Axis when going CV
		if (iNr == 2 && other->iNr == 1) {
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
		this->acceleration += ( mag * force / this->mass ) * TIME_STEP;
	}

	//mouse
	/*POINT p;
	HWND handle;
	handle = FindWindowA(NULL, "Gravity Simulation");
	if (GetCursorPos(&p))
	{
		if (ScreenToClient(handle, &p))
		{
			Vector mouse = Vector(p.x, p.y);

			Vector posV = mouse - this->position;
			double distance = posV.Lenght();
			Vector mag = posV / distance;

			double force = this->mass * MOUSE * G / pow(distance, 2);
			this->acceleration += mag * force / this->mass;
		}
	}//*/

	this->velocity += this->acceleration;
}

void Planet::updatePosition()
{
	this->position += this->velocity;
}

void Planet::render(SDL_Renderer* renderer)
{
	this->destRect.w = this->destRect.h = this->radius * 2;

	this->destRect.x = this->position.x - this->radius + WIDTH / 2;
	this->destRect.y = HIGHT - ( this->position.y - this->radius + HIGHT / 2 );			// Y upp

	SDL_RenderCopy(renderer, this->texture, 0, &destRect);
}
