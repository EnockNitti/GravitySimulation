#pragma once

#define ELIPTIC false
#define LOGL4 false
#define LOGL2 false
#define MANY true
#define SYSTEM false
#define TWOPLANETS false
#define SUNMOON false

#define TRACKS true
#define TRACKLEN 251
#define MAXACC 10000.0

#include <Windows.h>
#include <time.h>
#include <cmath>
#include "Vector.h"
#include <vector>
#include <condition_variable>
#include <thread>
#include <chrono>
#include "SDL.h"
#include "SDL_image.h"
#include "planet.h"
#include "Game.h"
#include "Display.h"
#include "Universe.h"


extern long unsigned int luiIterations;
extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern Game* game;
extern void InitDisplayThread();
extern CRITICAL_SECTION CriticalSection;
//extern int iNPlanets;
extern double dTimeStep;


//#define FPS 60
#define FPS 100
#define FRAMEDELAY ( 1000 / FPS )
#ifdef _DEBUG
#define DBGSPEED 1
#else
#define DBGSPEED 100
#endif

#define HIGHT 1000
#define WIDTH 1000
#define PI 3.14159
#define DENSITY 1.0


#if MANY 
#define G (1.0 / 2 )
#define TIMESTEP (2.0 / ( 10000000000.0 * DBGSPEED ))

#elif LOGL2
#define G (1.0 / 128.0)
#define TIMESTEP (2.0 / ( 1000000000.0 * DBGSPEED ))

#elif SUNMOON
#define G (1.0 / 64.0 )
#define TIMESTEP (2.0 / ( 1000000000.0 * DBGSPEED))

#elif TWOPLANETS
#define G (1.0 / 64.0 )
#define TIMESTEP (2.0 / ( 100000000.0 * DBGSPEED))

#elif ELIPTIC
#define G (1.0 / 64.0 )
#define TIMESTEP (2.0 / ( 100000000.0 * DBGSPEED))

#elif LOGL4
#define G (1.0 / 64.0 )
#define TIMESTEP (2.0 / ( 100000000.0 * DBGSPEED))

#else
#define G (1.0 / 64.0 )
#define TIMESTEP (2.0 / ( 10000000.0 * DBGSPEED))


#endif

#define MOUSE 100000.0
#define pi2 ( PI * 2)

