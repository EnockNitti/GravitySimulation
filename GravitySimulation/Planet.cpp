#include "main.h"

extern Game* game;


Planet::Planet(double mass, Vector position, Vector velocity, int iNr, double dL2Dist)
{
	this->radius = sqrt(cbrt(mass / DENSITY / PI / 3));
	if (this->radius < 1) this->radius = 1;

	this->acceleration = Vector();
	this->mass = mass;
	this->position = position;
	this->velocity = velocity * sqrt(dTimeStep);
//	this->velocity = velocity * dTimeStep;
	this->Momentum = this->velocity * mass;
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

/*************************************/

void Planet::updateVelocityInit(std::vector<Planet*>& Planets)
{
	for (int i = 0; i < iNPlanets; i++)
	{
		Planets[i]->acceleration.Zero();
	}
}

/*************************************/
#if 0
double Planet::updateAccs(std::vector<Planet*>& others, int iPNr )
{

	double dMaxAcc = 0;
	static 	double dHighAcc = 0;
	static Vector vForce;

	for (int i = iPNr; i < iNPlanets-1; i++)
	{
		Planet* other = others[ i+1 ];

		Vector posV;
		posV.x = other->position.x - this->position.x;
		posV.y = other->position.y - this->position.y;

		double distance2 = ((position.x - other->position.x) * (position.x - other->position.x) +
			(position.y - other->position.y) * (position.y - other->position.y));

		double distance = sqrt(distance2);
		Vector vForce = (posV * G ) / (distance * distance2);
		other->acceleration.x -= vForce.x * this->mass;
		other->acceleration.y -= vForce.y * this->mass;
		acceleration.x += vForce.x * other->mass;
		acceleration.y += vForce.y * other->mass;

		if (abs(acceleration.x) > dMaxAcc) dMaxAcc = abs(acceleration.x);
		if (abs(acceleration.y) > dMaxAcc) dMaxAcc = abs(acceleration.y);
		if (abs(other->acceleration.x) > dMaxAcc) dMaxAcc = abs(other->acceleration.x);
		if (abs(other->acceleration.y) > dMaxAcc) dMaxAcc = abs(other->acceleration.y);

	}
	if (dHighAcc < dMaxAcc * 0.9) {
		dHighAcc = dMaxAcc;
		printf("%e\n", dHighAcc);
	}

	return dMaxAcc * dTimeStep ;
}
#endif

/**********      Update accelerations  **************/

double Planet::updateAccs( int iPlanet, std::vector<Planet*> planets)
{
	double dMaxAcc = 0;
	static 	double dHighAcc = 0;

		for (int i = iPlanet + 1; i < iNPlanets; i++)
		{
			Planet* other = planets[ i ];
			if ( other->iNr >= 100) continue;

			Vector posV;
			posV.x = other->position.x - this->position.x;
			posV.y = other->position.y - this->position.y;

			double distance2 = (posV.x * posV.x) + (posV.y * posV.y);

			double distance = sqrt(distance2);
			Vector vGForce = (posV * G) / (distance * distance2);
			other->acceleration.x -= vGForce.x * this->mass;
			other->acceleration.y -= vGForce.y * this->mass;
			this->acceleration.x += vGForce.x * other->mass;
			this->acceleration.y += vGForce.y * other->mass;

			if (abs(this->acceleration.x) > dMaxAcc) dMaxAcc = abs(this->acceleration.x);
			if (abs(this->acceleration.y) > dMaxAcc) dMaxAcc = abs(this->acceleration.y);
			if (abs(other->acceleration.x) > dMaxAcc) dMaxAcc = abs(other->acceleration.x);
			if (abs(other->acceleration.y) > dMaxAcc) dMaxAcc = abs(other->acceleration.y);

			luiIterations++;
		}

		if (dHighAcc < dMaxAcc * 0.9) {
			dHighAcc = dMaxAcc;
			printf("%e\n", dHighAcc);
		}
	return dMaxAcc * dTimeStep;
}


/*************************************/

void Planet::updateVelocityAndPosition()
{
	this->velocity += acceleration * dTimeStep;		
//	EnterCriticalSection(&CriticalSection);
	this->position += this->velocity;
//	LeaveCriticalSection(&CriticalSection);
}

// Render one planet
void Planet::render()
{
	destRect.w = destRect.h = (int)radius * 2;

//	EnterCriticalSection(&CriticalSection);

	destRect.x = (int)(position.x - radius + WIDTH / 2);
	destRect.y = HIGHT - (int)(position.y + radius + HIGHT / 2);			// Y upp, center origo

//	LeaveCriticalSection(&CriticalSection);			// But here

	if (SDL_RenderCopy(renderer, texture, 0, &destRect) != 0)
	{
		printf("%s\n", SDL_GetError());
		exit(1);		
	}
}
