#pragma once

#define ELIPTIC true
#define LOGL4 false
#define LOGL2 false
#define MANY false
#define SYSTEM false
#define TWOPLANETS false
#define SUNMOON false

#define TRACKS true
#define TRACKLEN 252

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
extern int iNPlanets;
extern double dTimeStep;


//#define FPS 60
#define FPS 100
#define FRAMEDELAY ( 1000 / FPS )

#define HIGHT 1000
#define WIDTH 1000
#define PI 3.14159
#define DENSITY 1.0

#if MANY 
//#define TIME_STEP ( 1.0 / 0x10000000000 )

#define G (1.0)
//#define TIME_STEP ( 1.0 / 0x100000000 )
#define TIME_STEP ( dTimeStep )
#define MINACC 1e-10
#define MAXACC 1e-7




#elif LOGL2

#define G (1.0 / 128)
//#define TIME_STEP ( 1.0 / 0x100000000 )
#define TIME_STEP ( dTimeStep )
#define MINACC 1e-7
#define MAXACC 1e-5


#else
#define G (1.0 / 64 )
#define DELTAVMAX (2.0 / 10000000000)
#define DELTAVMIN (0.125 / 10000000000)
#define TIMESTEP (2.0 / 1000000000)


#endif

#define MOUSE 100000.0
#define pi2 ( PI * 2)

