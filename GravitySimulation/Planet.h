#pragma once

#include "Vector.h"
#include <vector>
#include "SDL_image.h"

#define TIME_STEP ( 1.0 / 0x10000000 )

#define ELIPTIC false
#define LOGL4 false
#define LOGL2 true


struct Planet
{
	double radius, mass;
	Vector position, velocity, acceleration, Momentum;
	int iNr, dL2Dist;  
	
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;

	Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer, int iNr = 0, double dL2Dist = 0 );

	void updateVelocity(std::vector<Planet*>& others);
	void updatePosition();
	
	void render(SDL_Renderer* renderer);
};