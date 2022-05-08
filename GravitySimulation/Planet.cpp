#include "main.h"

extern Game* game;


Planet::Planet(double mass, Vector position, Vector velocity, int iNr, double dL2Dist)
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

	if (iNr < 100)
		tempSurface = IMG_Load("planet.png");
	else
		tempSurface = IMG_Load("Marker.png");
	q = SDL_GetError();

	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	q = SDL_GetError();

	SDL_FreeSurface(tempSurface);
}

static double dMaxAcceleration = 0;

void Planet::updateVelocityInit(std::vector<Planet*>& Planets)
{
	for (int i = 0; i < iNPlanets; i++)
	{
		Planets[i]->acceleration.Zero();
	}
}

#define MAXACC 1e-7

#if 0

void Planet::updateVelocityFirst(std::vector<Planet*>& others)
{
	Vector acceleration;

	for (int i = 1; i < iNPlanets; i++)
	{
		Planet* other = others[i];
		other->acceleration.Zero();

		Vector posV;
		posV.x = other->position.x - this->position.x;
		posV.y = other->position.y - this->position.y;

		double distance2 = ((position.x - other->position.x) * (position.x - other->position.x) +
			(position.y - other->position.y) * (position.y - other->position.y));

		double distance = sqrt(distance2);
		Vector mag = posV / distance;
		Vector mag2 = mag;

		acceleration = mag * other->mass * G / distance2 * TIME_STEP;
		other->acceleration -= ( mag2 * this->mass * G / distance2 * TIME_STEP );
//		printf(" ");
	}

/*
	if (acceleration.x > dMaxAcceleration)
	{
		dMaxAcceleration = acceleration.x;
		printf("%g\n", dMaxAcceleration);

	}
	if (acceleration.y > dMaxAcceleration)
	{
		dMaxAcceleration = acceleration.y;
		printf("%g\n", dMaxAcceleration);
	}
*/
	if (acceleration.x > MAXACC) acceleration.x = MAXACC;
	if (acceleration.y > MAXACC) acceleration.y = MAXACC;
	if (acceleration.x < -MAXACC) acceleration.x = -MAXACC;
	if (acceleration.y < -MAXACC) acceleration.y = -MAXACC;

	this->velocity += acceleration;
	luiIterations++;
}
#endif

void Planet::updateVelocityOthers(std::vector<Planet*>& others, int iPNr )
{
	for (int i = iPNr; i < iNPlanets-1; i++)
	{
		Planet* other = others[ i+1 ];

		Vector posV;
		posV.x = other->position.x - this->position.x;
		posV.y = other->position.y - this->position.y;

		double distance2 = ((position.x - other->position.x) * (position.x - other->position.x) +
			(position.y - other->position.y) * (position.y - other->position.y));

		double distance = sqrt(distance2);
		Vector mag = posV / distance;
		Vector mag2 = mag;
		acceleration += mag * other->mass * G / distance2 * TIME_STEP;
		other->acceleration -= mag2 * this->mass * G / distance2 * TIME_STEP;
		if (acceleration.x > MAXACC) acceleration.x = MAXACC;
	}

	if (acceleration.x > MAXACC) acceleration.x = MAXACC;
	if (acceleration.y > MAXACC) acceleration.y = MAXACC;
	if (acceleration.x < -MAXACC) acceleration.x = -MAXACC;
	if (acceleration.y < -MAXACC) acceleration.y = -MAXACC;

	this->velocity += acceleration;

	luiIterations++;
}

void Planet::updatePosition()
{
	EnterCriticalSection(&CriticalSection);
	this->position += this->velocity;
	LeaveCriticalSection(&CriticalSection);
}

// Render one planet
void Planet::render()
{
	destRect.w = destRect.h = (int)radius * 2;

	destRect.x = (int)(position.x - radius + WIDTH / 2);
	destRect.y = HIGHT - (int)(position.y + radius + HIGHT / 2);			// Y upp, center origo

	if (SDL_RenderCopy(renderer, texture, 0, &destRect) != 0)
	{
		printf("%s\n", SDL_GetError());
		exit(1);		
	}
}
