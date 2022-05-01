#include "main.h"

Game::Game() {};
Game::~Game() {};

double nsign(double b, double a)
{
	a = -abs( a);
	if( b < 0 )
		a = abs(a);
	return a;
}

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
		else
			printf("%s\n", SDL_GetError());

		isRunning = true;
	}

	// 4 Planets in a circle
/*	universe.addPlanet(new Planet(100000, Vector(-400, 0  ), Vector(0, 1) ));
	universe.addPlanet(new Planet(100000, Vector( 400, 0 ), Vector(0, -1) ));
	universe.addPlanet(new Planet(100000, Vector( 0, -400), Vector(-1, 0) ));
	universe.addPlanet(new Planet(100000, Vector( 0, 400 ), Vector(1, 0) ));//*/

#if MANY

	// Random planets
//#define	RAND_MAX 1000;
	srand(  (unsigned int)time(NULL) );
	for (int i = 0; i < 25; i++)
	{
		int x = ( rand() % WIDTH - 450 ) / 2;
		int y = ( rand() % HIGHT- 450 ) / 2;
		double xv = (rand() - RAND_MAX / 2) / 50000.0;
		double yv = (rand() - RAND_MAX / 2) / 50000.0;
		xv = nsign(x, xv);
		yv = nsign(y, yv);

		universe.addPlanet(new Planet( rand() % 100 + 100,	Vector( x, y), Vector( xv, yv ), i ));
	}//*/
	double d = ((rand() - 500.0) / 500.0);
#endif

	// Orbiting planets
/*	universe.addPlanet(new Planet(100000, Vector( 0 , 0 ), Vector(0, 0 ) ));		//   "Sun"
	universe.addPlanet(new Planet(1000, Vector(	0, 300 ), Vector( 0.75, 0 ) , 1));
	universe.addPlanet(new Planet(1000, Vector( 300 , -300 ), Vector( -0.25, 0.2) , 0));
	universe.addPlanet(new Planet(1000, Vector( 0, -300 ), Vector(-0.75, 0) ));//*/

#if ELIPTIC

	double dSun = 100000.0;
	double dPlanet1 = 1000.0;

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0) , 0));		//   "Sun"
	universe.addPlanet(new Planet(dPlanet1, Vector( 300, 300 ), Vector( 0.3, -0.3) , 1));

#endif


#if	LOGL4
		// L4

	double dSun = 100000.0;
	double dPlanet1 = 1000.0;
	double dL4 = 0.01;
	double z = 250;
	double speed = sqrt( G * ( (dSun + dPlanet1 ) / z ));

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0) ));		//   "Sun"
	universe.addPlanet(new Planet(dPlanet1, Vector(0, z), Vector(speed, 0) , 1 ));	// Planet
	universe.addPlanet(new Planet(dL4, Vector(cos(30.0 / 360 * pi2) * z, sin(30.0 / 360 * pi2) * z),
		Vector(sin(30.0 / 360 * pi2) * speed, -cos(30.0 / 360 * pi2) * speed) , 2));//*/	// Satellite

	iNPlanets = universe.planets.size();

	// Marker
	universe.addPlanet(new Planet(dL4, Vector(cos(30.0 / 360 * pi2) * z, sin(30.0 / 360 * pi2) * z),
		Vector( 0,0 ) , 100));//*/


#endif


#if TWOPLANETS
#if 0	// Very close
	double dSun = 100000.0;
	double dPlanet = 10.0;
	double O0 = 100;
	double O1 = 200;
	double O2 = 300;
	double O3 = 400;
	double O4 = 500;

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0) ));		//   "Sun"

	Vector Pos(0, O3);
	Vector Vel(sqrt((G * ((dSun + dPlanet) / O3))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 1));
/*
	Pos = Vector(0+12, O3);
	Vel = Vector(sqrt((G* ((dSun + dPlanet) / O3))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 2));
*/
	iNPlanets = universe.planets.size();

#else
// an another variation
	double dSun = 100000.0;
	double dPlanet = 100.0;
	double O0 = 100;
	double O1 = 200;
	double O2 = 300;
	double O3 = 319;
	double O4 = 500;

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0) ));		//   "Sun"

	Vector Pos( 0, O2);
	Vector Vel(sqrt((G* ((dSun + dPlanet) / O2))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 1));

	Pos = Vector( 0, O3);
	Vel = Vector(sqrt((G * ((dSun + dPlanet) / O3))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 2));

	iNPlanets = universe.planets.size();

#endif
#endif




#if SYSTEM

	double dSun = 100000.0;
	double dPlanet = 100.0;
	double O0 = 100;
	double O1 = 200;
	double O2 = 300;
	double O3 = 400;
	double O4 = 500;

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0) ));		//   "Sun"
	
	Vector Pos(0, O0);
	Vector Vel(sqrt((G * ((dSun + dPlanet) / O0))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 1));

	Pos = Vector( 0, O1 );
	Vel = Vector(sqrt((G * ((dSun + dPlanet) / O1))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 2));

	Pos = Vector(0, O2);
	Vel = Vector(sqrt((G * ((dSun + dPlanet) / O2))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 3));

	Pos = Vector(0, O3);
	Vel = Vector(sqrt((G * ((dSun + dPlanet) / O3))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 4));

/*	// a rough planet :)
	Pos = Vector(0, O4);
	Vel = Vector(sqrt((G * ((dSun + dPlanet) / O3)) -1.0), -0.3);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 5));
*/
	iNPlanets = universe.planets.size();

#endif

#if	LOGL2
	double dSun = 1000000.0;
//	double dSun = 100000.0;
	double dPlanet1 = 1000.0;
	double dL2 = 0.01;
	double z = 250;
	double speed = sqrt(G * ((dSun + dPlanet1) / z));

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0), 0 ));		//   "Sun"
	universe.addPlanet(new Planet(dPlanet1, Vector(0, z), Vector(speed, 0) , 1));

	// Lagrange L2
	double dL2Dist = z * std::cbrt(dPlanet1 / ( 3 * ( dSun + dPlanet1 )));		// First aprox
	dL2Dist += 0.401793935;			// The fiddle factor needed for the L2 satellite to stay in place for at least 1.5 of a revolution..... :)
	double speedL2 = speed * (z + dL2Dist) / z;
	

	// L2 satellite
	universe.addPlanet(new Planet( dL2, Vector(0, z + dL2Dist), Vector(speedL2, 0) , 2));//*/

	iNPlanets = universe.planets.size();

	// Theoretical(Marker) postition for L2  ( red )
	universe.addPlanet(new Planet(0.00001, Vector(0, z + dL2Dist), Vector(0, 0) , 101, dL2Dist));//*/
#endif

	// This correction is needed for "unsymmetrical" systems like sun-earth
	universe.MomentumAdjust();

	InitDisplayThread();

}

void Game::update()
{
	this->universe.update();
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

	case SDL_KEYDOWN:
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
					universe.addPlanet(new Planet(1000, mPos, Vector(-2, 0) ));
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