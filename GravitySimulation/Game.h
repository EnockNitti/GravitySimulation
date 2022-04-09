#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Universe.h"

#include <iostream>

#define HIGHT 900
#define WIDTH 900
#define PI 3.14159
#define DENSITY 1.0
#define G (1.0 / 128)
#define MOUSE 100000.0

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

	bool running() { return isRunning; };

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

};