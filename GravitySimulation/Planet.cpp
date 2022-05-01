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

void Planet::updateVelocity(std::vector<Planet*>& others)
{
	static long unsigned int luiLastIterations = 0;

	this->acceleration = Vector();

	for (int i = 0; i < iNPlanets; i++)
	{
		if (this->iNr >= 100) continue;		// Marker is uppdated in Display::fRender
		Planet* other = others[i];

		//don't compute to itself
		if (other == this ) continue;

		Vector posV = other->position - this->position;
//		Had problems with inlining here /Ob2. 
//		printf("%g %g %i %i\n", posV.x, posV.y, this->iNr, other->iNr);
//		printf("%g %g %g %g\n", this->position.x, this->position.y, other->position.x, other->position.y);

		double distance2 = ((position.x - other->position.x) * (position.x - other->position.x) +
			(position.y - other->position.y ) * (position.y - other->position.y ));

		double distance = sqrt( distance2);
		Vector mag = posV / distance;

		this->acceleration += mag * other->mass * G / distance2 * TIME_STEP;
	}

	this->velocity += this->acceleration;
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
