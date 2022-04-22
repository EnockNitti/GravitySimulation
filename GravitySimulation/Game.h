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
	void render();
	void clean();
	void handleEvents();
	bool isRunning = false;
	bool running() { return isRunning; };
//	SDL_Renderer* renderer = NULL;
//	SDL_Renderer * Getrenderer(){ return renderer; };

private:
//	SDL_Window* window = NULL;

};