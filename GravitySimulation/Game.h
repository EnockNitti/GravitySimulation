#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Universe.h"
#include "Planet.h"

#include <iostream>


class Game {

public:
	Game();
	~Game();
	Universe universe;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void update();
	void clean();
	void handleEvents();
	bool isRunning = false;
	bool running() { return isRunning; };
//	void AddDoubblePlanet(Vector Pos, double dMass, double dDistance, int iNr);
	void AddDoubblePlanet(Vector CPos, double dMass, double dDistance, int iNr );
	void PlanetOrbit( Planet *pCPlanet, double AtAng, double dMass, double dDistance, int iNr);

private:

};