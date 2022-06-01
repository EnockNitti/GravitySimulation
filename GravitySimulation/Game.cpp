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

#if MANY
	// A random assortment of planets, rotating clockwise around a sun
	double dSun = 100000.0;
	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0)));		//   "Sun"
//#define	RAND_MAX 1000;
	srand(  (unsigned int)time(NULL) );
	for (int i = 0; i < 10; i++)
	{
		int x = (rand() % WIDTH - 450) / 2;
		int y = (rand() % HIGHT - 450) / 2;

//		double dMass = rand() % 100 + 100.0;
		double dMass = rand() % 500 + 100.0;
		double dDistance = sqrt(x * x + y * y);
		double dSpeed = sqrt(G * ((dSun + dMass) / dDistance));
//		double xv = speed + (rand() - RAND_MAX / 2) / 100.0;
//		double yv = speed + (rand() - RAND_MAX / 2) / 100.0;
		double xv = dSpeed;
		double yv = dSpeed;
		double dLowSpeed = dSpeed / 5;

		if (x > 0) {
			if (y > 0) {
				xv = dLowSpeed;
				if (yv > 0) yv = -yv;
			}
			else
			{
				yv = dLowSpeed;
				if (xv > 0) xv = -xv;
			}
		}
		else {
			if (y > 0) {
				yv = dLowSpeed;
				if (xv < 0) xv = -xv;
			}
			else
			{
				xv = dLowSpeed;
				if (yv < 0) yv = -yv;
			}
		}

		universe.addPlanet(new Planet( dMass, Vector( x, y), Vector( xv, yv ), i+1 ));
	}//*/


#endif

#if ELIPTIC

	double dSun = 100000.0;
	double dPlanet1 = 10.0;

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0) , 0));		//   "Sun"
	universe.addPlanet(new Planet(dPlanet1, Vector( 300, 300 ), Vector( 0.1, -0.1) , 1));

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

	// Marker    Red
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

#endif
#endif

#if SUNMOON
	double dSun = 100000.0;
	double dPlanet = 100.0;
	double dMoon = 1;

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0)));		//   "Sun"

	Vector Pos(0, 300);
	Vector Vel(sqrt((G* ((dSun + dPlanet) / 300 ))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel, 1));

	Pos = Vector(0, 320);
	Vel += Vector(sqrt((G * (( dPlanet+ dMoon) / 20 ))), 0.0);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel, 2));

#endif

#if SYSTEM

	double dSun = 100000.0;
	double dPlanet = 100.0;
	double O0 = 100;
	double O1 = 200;
	double O2 = 300;
	double O3 = 400;
	double O4 = 350;

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

	// a rough planet :)
	Pos = Vector(0, O4);
	Vel = Vector(sqrt((G * ((dSun + dPlanet) / O3)) -1.0), -0.3);
	universe.addPlanet(new Planet(dPlanet, Pos, Vel , 5));

#endif

#if	LOGL2
	double dSun = 1000000.0;
	double dPlanet1 = 1000.0;
	double dL2 = 0.01;
	double z = 250;
	double speed = sqrt(G * ((dSun + dPlanet1) / z));

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0), 0 ));		//   "Sun"
	universe.addPlanet(new Planet(dPlanet1, Vector(0, z), Vector(speed, 0) , 1));

	// Lagrange L2

	double dL2Dist = z * std::cbrt(dPlanet1 / ( 3 * ( dSun + dPlanet1 )));		// First aprox
	dL2Dist += 0.397667211;			// The fiddle factor needed for the L2 satellite to stay in place for at least for a revolution..... :)
	double speedL2 = speed * (z + dL2Dist) / z;
	

	// L2 satellite
	universe.addPlanet(new Planet( dL2, Vector(0, z + dL2Dist), Vector(speedL2, 0) , 2));//*/

//	iNPlanets = universe.planets.size();

	// Theoretical(Marker) postition for L2  ( red )
	universe.addPlanet(new Planet(0.00001, Vector(0, z + dL2Dist), Vector(0, 0) , 101, dL2Dist));//*/
#endif

#if BINARY

/*	Binary Star System Orbital Period :

	Check the semi - major axis, first body, second body mass.
		Add the masses.Multiply the sum with the gravitational constant.
		Divide the cube of semi - major axis by the product.
		Find the square root of the result.
		Multiply it with the 2π to obtain binary system orbital period.

		Orbital period binary objects = 2 * π * √(a³ / (G * (M₁ + M₂)))
*/

	double dDistance = 100;		
	double dMass = 100;
	// This works, don't know why 
//	double dPeriode = 2 * PI * sqrt((dDistance * dDistance * dDistance * 2) / (G * (dMass + dMass)));
//	dSpeed = dDistance * PI / dPeriode;			// tangential
	// This works, don't know why 
	double dSpeed = 1.0 / (2 * sqrt( dDistance / (G * 2 * dMass )));

	Vector Pos( 0, dDistance / 2 );
	Vector Vel( dSpeed, 0.0 );
	universe.addPlanet(new Planet(dMass, Pos, Vel, 1 ));

	Vector Pos1( 0, -dDistance / 2 );
	Vector Vel1( -dSpeed, 0.0 );
	universe.addPlanet( new Planet( dMass, Pos1, Vel1, 2 ));

	AddDoubblePlanet(Vector( 300, 300), 100, 100, 3);

#elif RANDSYSTEM

	double dSun = 100000.0;
	double dMass = 100.0;
	double dDist = 250;
	double alpha = PI / 4;
	srand(time(NULL));

	universe.addPlanet(new Planet(dSun, Vector(0, 0), Vector(0, 0), 0));		//   "Sun"

	for (int i = 0; i < 30; i++)
	{
		dDist = rand() % 450 + 50;
		alpha = double(rand() % int( 2 * PI * 1000 ));
		alpha /= 1000;

		PlanetOrbit(universe.planets[0], alpha, dMass, dDist, i + 1 );
	}

#endif

	// This correction is needed for "unsymmetrical" systems like sun-earth
	universe.MomentumAdjust();

	InitDisplayThread();

}
#if 1
/**************** Add a doubble planet ******************/

void Game::AddDoubblePlanet(Vector CPos, double dMass, double dDistance, int iNr )
{
	double dSpeed = 1.0 / (2 * sqrt(dDistance / (G * 2 * dMass)));

	Vector Pos = CPos;
	Pos.y = Pos.y + dDistance / 2;
	Vector Vel(dSpeed, 0.0);
	universe.addPlanet(new Planet(dMass, Pos, Vel, iNr ));

	Vector Pos1 = CPos;
	Pos1.y = Pos1.y - dDistance / 2;
	Vector Vel1(-dSpeed, 0.0);
	universe.addPlanet(new Planet(dMass, Pos1, Vel1, iNr+1));
}

/********************** Add a planet in cirkulat orbit around Central planet at a specified distance and angle( +X axis )   *******************/
void Game::PlanetOrbit(Planet *pCPlanet, double alpha, double dMass, double dDistance, int iNr )
{
	Vector Position(dDistance, 0.0);
	Position.Rotate( alpha );
	Position = pCPlanet->position + Position;

	double dSpeed = sqrt(G * (( pCPlanet->mass + dMass ) / dDistance ));
	Vector Velocity( 0.0, -dSpeed );
	Velocity.Rotate( alpha );
	Velocity = pCPlanet->velocity + Velocity;

	universe.addPlanet(new Planet( dMass, Position, Velocity, iNr ));




}
#endif


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