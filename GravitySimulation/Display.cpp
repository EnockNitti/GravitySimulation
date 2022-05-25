
#include "Main.h"

// Run rendering in a separate thread at 60/100 fps

SDL_Thread* pRThread;

static int fRThread(void* pv)
{
	Display cDisplay;
	cDisplay.fRender();
	return 0;
}

//**********************************

void InitDisplayThread()
{
	pRThread = SDL_CreateThread( fRThread, "RThread", (void*)NULL);
	if (!pRThread) {
		printf("%s\n", SDL_GetError());
		exit(1);		// Error return
	}
}

//********************************** 
	// "atomic read"   :)  

Vector GetPlanetPosition( Vector * pPosV )
{
	Vector PosV;
	memcpy( &PosV, pPosV, sizeof( PosV ));
	return PosV;
}

//********************************** 
/*
// "atomic write"   :)  
void SetPlanetPosition( Vector *pPosition, Vector Position)
{
	Vector PosV;
	memcpy( pPosition, &Position, sizeof(PosV));
}
*/
//********************************** 

// Render planets, present new universe
int Display::fRender()
{

	static int iCnt = 0;
	static SDL_Texture* tOldImage = NULL;
	SDL_Surface* sOldImage = NULL;
	static int i = 0;

	Planet* pPlanet = game->universe.planets.at(1);  // For use with L2 and L4, always related to planet 1
	Planet* pLagrange = game->universe.planets.back();  // For use with L2 and L4

	for (;; ) {

		if (SDL_RenderClear(renderer) != 0)
			break;
#if TRACKS
		if (tOldImage) {
			if (SDL_SetTextureBlendMode(tOldImage, SDL_BLENDMODE_BLEND) != 0)
				break;
			if (SDL_SetTextureAlphaMod(tOldImage, TRACKLEN ) != 0)
				break;
			if (SDL_RenderCopy(renderer, tOldImage, NULL, NULL) != 0)
				break;
			SDL_DestroyTexture(tOldImage);

		}
#endif
		SDL_Delay( FRAMEDELAY );

#if LOGL4
		if (pLagrange->iNr >= 100) {
			Vector Position = GetPlanetPosition(&pPlanet->position);
			Position.Rotate(pi2 * -60 / 360);
			pLagrange->position = Position;
		}
#endif
#if LOGL2
		if (pLagrange->iNr >= 100)
		{
			Vector Position = GetPlanetPosition(&pPlanet->position);
			Position.Extend( pLagrange->dL2Dist );
			pLagrange->position = Position;
		}
#endif

		// render all new stuff
		for (auto& planet : game->universe.planets) {
			planet->render();
		}

#if TRACKS
		{
			SDL_Surface* saveSurface = NULL;
			SDL_Surface* infoSurface = NULL;

			infoSurface = SDL_GetWindowSurface(window);
			if (infoSurface == NULL) {
				break;
			}

			int nBytes = infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel;
			unsigned char* pixels = new unsigned char[nBytes];
			if (infoSurface == NULL) {
				break;
			}

			if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format,
				pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				break;
			}

			saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h,
				infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask,
				infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
			if (saveSurface == NULL) {
				break;
			}

			tOldImage = SDL_CreateTextureFromSurface( renderer, saveSurface);
			if (!tOldImage) {
				break;
			}
			//*/
			delete[] pixels;
			SDL_FreeSurface(sOldImage);
			SDL_FreeSurface(infoSurface);
		}
		SDL_RenderPresent(renderer);
	}
	printf("%s\n", SDL_GetError());
	#endif
	exit(1);		// Error return
}
