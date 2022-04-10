#include "SDL.h"
#include "Game.h"
#include <Windows.h>

/*
 "high Speed" gravity simulation.
 On my system I get ~15000000 iteration/revolution on a 2 planet system. Revolution time: ~12 S, CPU load ~13%
 Your mileage may vary. Change TIME_STEP in planet.h to change speed.
 You need SDL2.lib, SDL2main.lib, zlib1.dll, libpng16-16.dll, SDL2.dll, SDL2_image.dll,
 and SDL-includes to run this when using VS2019

 Corrent config is a test of L2

 Just modified code from GitHub/Feeeeddmmmeee
*/

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 uiNow;
	Uint32 uiTimeStart = 0;

	game = new Game();
	game->init("Gravity Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HIGHT, false);

	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	while (game->running())
	{
		static int i = 0;

		uiNow = SDL_GetTicks();
		game->handleEvents();
		game->update();

		if (uiNow >= uiTimeStart + frameDelay)
		{
			uiTimeStart = uiNow + frameDelay;
			game->render();
		}
	}

	//ShowWindow(GetConsoleWindow(), SW_RESTORE);
	game->clean();

	return 0;
}