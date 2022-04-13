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


//		SDL_Surface* tempSurface;
//		this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);


		isRunning = true;
	}

	// 4 Planets in a circle
/*	universe.addPlanet(new Planet(100000, Vector(-400, 0  ), Vector(0, 1), renderer));
	universe.addPlanet(new Planet(100000, Vector( 400, 0 ), Vector(0, -1), renderer));
	universe.addPlanet(new Planet(100000, Vector( 0, -400), Vector(-1, 0), renderer));
	universe.addPlanet(new Planet(100000, Vector( 0, 400 ), Vector(1, 0), renderer));//*/

/*	// Random planets
	srand(time(NULL));
	for (int i = 0; i < 25; i++)
	{
		universe.addPlanet(new Planet(10.0 + std::rand() % 991, Vector(std::rand() % width, std::rand() % height), Vector(0, 0), renderer));
	}//*/

	// Orbiting planets
/*	universe.addPlanet(new Planet(100000, Vector( 0 , 0 ), Vector(0, 0 ), renderer));		//   "Sun"
	universe.addPlanet(new Planet(1000, Vector(	0, 300 ), Vector( 0.75, 0 ), renderer, 1));
	universe.addPlanet(new Planet(1000, Vector( 300 , -300 ), Vector( -0.25, 0.2), renderer, 0));
	universe.addPlanet(new Planet(1000, Vector( 0, -300 ), Vector(-0.75, 0), renderer));//*/


#if ELIPTIC

	double dSun = 100000.0;
	double dPlanet1 = 1000.0;

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0), renderer, 0));		//   "Sun"
	universe.addPlanet(new Planet(dPlanet1, Vector( 300, 300 ), Vector( 0.3, -0.3), renderer, 1));

#endif


#if	LOGL4
		// L4

	double dSun = 100000.0;
	double dPlanet1 = 1000.0;
	double dL4 = 0.01;
	double z = 250;
	double speed = sqrt( G * ( (dSun + dPlanet1 ) / z ));

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0), renderer));		//   "Sun"
	universe.addPlanet(new Planet(dPlanet1, Vector(0, z), Vector(speed, 0), renderer, 1 ));
	universe.addPlanet(new Planet(dL4, Vector(cos(30.0 / 360 * pi2) * z, sin(30.0 / 360 * pi2) * z),
		Vector(sin(30.0 / 360 * pi2) * speed, -cos(30.0 / 360 * pi2) * speed), renderer, 2));//*/
	// Marker
	universe.addPlanet(new Planet(dL4, Vector(cos(30.0 / 360 * pi2) * z, sin(30.0 / 360 * pi2) * z), Vector( 0,0 ), renderer, 100));//*/


#endif


#if	LOGL2
	double dSun = 1000000.0;
//	double dSun = 100000.0;
	double dPlanet1 = 1000.0;
	double dL2 = 0.01;
	double z = 250;
	double speed = sqrt(G * ((dSun + dPlanet1) / z));

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0), renderer));		//   "Sun"
	universe.addPlanet(new Planet(dPlanet1, Vector(0, z), Vector(speed, 0), renderer, 1));

	// Lagrange L2
	double dL2Dist = z * std::cbrt(dPlanet1 / ( 3 * ( dSun + dPlanet1 )));		// First aprox
	dL2Dist += 0.401793935;			// The fiddle factor needed for the L2 satellite to stay in place for at least 1.5 of a revolution..... :)
	double speedL2 = speed * (z + dL2Dist) / z;
	
	// L2 satellite
	universe.addPlanet(new Planet( dL2, Vector(0, z + dL2Dist), Vector(speedL2, 0), renderer, 4));//*/

	// Theoretical postition for L2  ( red )
	universe.addPlanet(new Planet( 0.00001, Vector(0, z + dL2Dist), Vector(0, 0), renderer, 101, dL2Dist ));//*/

#endif

	// This correction is needed for "unsymmetrical" systems like earth-moon
	universe.MomentumAdjust();
}

void Game::update()
{
	this->universe.update();
}

extern bool saveScreenshotBMP(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer);


// Clear "universe", Render planets, present new universe
void Game::render()
{
	static int iCnt = 0;
	const char* p;
	SDL_Texture* OldImage;

	OldImage = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HIGHT);

	if (iCnt++ < 100 || true) {
		SDL_Texture* OldImage = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HIGHT);
		p = SDL_GetError();

		SDL_RenderClear(renderer);

		SDL_SetTextureBlendMode(OldImage, SDL_BLENDMODE_BLEND);
		p = SDL_GetError();
		SDL_SetTextureAlphaMod(OldImage, 250);
		p = SDL_GetError();
		SDL_RenderCopy(renderer, OldImage, NULL, NULL);
		p = SDL_GetError();

		//Planets
		this->universe.render(this->renderer);


		if (iCnt == 100) {
			bool OK = saveScreenshotBMP("D:/test.bmp", window, renderer);
		}



	}
	else {
		SDL_SetTextureBlendMode(OldImage, SDL_BLENDMODE_NONE);
		p = SDL_GetError();
		SDL_SetTextureAlphaMod(OldImage, 250);
		p = SDL_GetError();
		SDL_Rect Rect;
		Rect.x = 0;
		Rect.y = 0;
		Rect.w = WIDTH;
		Rect.y = HIGHT;
		SDL_RenderCopy(renderer, OldImage, &Rect, &Rect);
/*
		int SDL_RenderReadPixels(SDL_Renderer * renderer,
			const SDL_Rect * rect,
			Uint32 format,
			void* pixels, int pitch);
*/


	}
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