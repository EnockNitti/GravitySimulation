#include "Game.h"

#include <time.h>
#include <Windows.h>
#include <cmath>

Game::Game() {};
Game::~Game() {};

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}

	// 4 Planets in a circle
/*	universe.addPlanet(new Planet(100000, Vector(200, 400), Vector(0, 1), renderer));
	universe.addPlanet(new Planet(100000, Vector(600, 400), Vector(0, -1), renderer));
	universe.addPlanet(new Planet(100000, Vector(400, 200), Vector(-1, 0), renderer));
	universe.addPlanet(new Planet(100000, Vector(400, 600), Vector(1, 0), renderer));//*/

/*	// Random planets
	srand(time(NULL));
	for (int i = 0; i < 25; i++)
	{
		universe.addPlanet(new Planet(10.0 + std::rand() % 991, Vector(std::rand() % width, std::rand() % height), Vector(0, 0), renderer));
	}//*/

	// Orbiting planets
	universe.addPlanet(new Planet(100000, Vector(width/2, height/2), Vector(0, 0), renderer));		//   "Sun"
	universe.addPlanet(new Planet(1000, Vector(width / 2, height / 2 - height / 4), Vector(2, 0), renderer, 1));
//	universe.addPlanet(new Planet(1000, Vector(width * 9 / 10 , height * 9 / 10 ), Vector( -0.25, 0.2), renderer, 1));
//	universe.addPlanet(new Planet(1000, Vector(width/2, height/2 + height/4), Vector(-2, 0), renderer));//*/
	
	double z = height / 4;
	double x = width / 2;
	double pi2 = 3.14159 * 2;

	// L2
	universe.addPlanet(new Planet( 0.1, Vector( x + cos( 30.0 / 360 * pi2 ) * z , height/2 - height/4 + sin( 30.0 / 360 * pi2) * z ),
		Vector( sin(30.0 / 360 * pi2) * 2 , cos(30.0 / 360 * pi2) * 2 ), renderer, 2));//*/

	// Lagrange distance L1 L2. Not working
//	double dDist = ( height / 2 ) * std::cbrt( 1000.0 / ( 3 * 100000.0 ));
//	universe.addPlanet(new Planet( 0.1, Vector(width/2, height/2 - height/4 - dDist * 0.635), Vector( 2, 0), renderer));//*/

	// This correction is needed for "unsymmetrical" systems like earth-moon

	universe.MomentumAdjust();
}

void Game::update()
{
	this->universe.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	this->universe.render(this->renderer);

	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{

	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	//adding planets
	/*case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			POINT p;
			HWND handle;
			handle = FindWindowA(NULL, "Gravity Simulation");
			if (GetCursorPos(&p))
			{
				if (ScreenToClient(handle, &p))
				{
					Vector mPos = Vector(p.x, p.y);
					universe.addPlanet(new Planet(1000, mPos, Vector(-2, 0), renderer));
				}
			}

			break;
		}//*/
	}

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}