#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Universe.h"
#include "Planet.h"

#include <iostream>

#define HIGHT 900
#define WIDTH 900
#define PI 3.14159
#define DENSITY 1.0
#if MANY 
#define G (4.0)
#else
#define G (1.0 / 128)
#endif

#define MOUSE 100000.0
#define pi2 ( PI * 2)




class Game {

public:
	Game();
	~Game();
	Universe universe;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void update();
	void render();
	void clean();
	void handleEvents();
	bool isRunning = false;
	bool running() { return isRunning; };
	SDL_Renderer* renderer = NULL;
	SDL_Renderer * Getrenderer(){ return renderer; };

private:
	SDL_Window* window = NULL;

};