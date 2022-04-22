
#include "Main.h"

// Run rendering in a separate thread at 60 fps

SDL_Thread* pRThread;

static int fRThread(void* pv)
{
	Display cDisplay;
	cDisplay.fRender();
	return 0;
}

//**********************************

void Display::Init()
{
	pRThread = SDL_CreateThread( fRThread, "RThread", (void*)NULL);
	if (!pRThread) {
		printf("%s\n", SDL_GetError());
		exit(1);		// Error return
	}
}

//**********************************

#if 1
// Clear "universe", Render planets, present new universe
int Display::fRender()
{
#if 1

	static int iCnt = 0;
	static SDL_Texture* tOldImage = NULL;
	SDL_Surface* sOldImage = NULL;
	static int i = 0;

	for (;; ) {

		if (SDL_RenderClear(renderer) != 0)
			break;
		if (tOldImage) {
			if (SDL_SetTextureBlendMode(tOldImage, SDL_BLENDMODE_BLEND) != 0)
				break;
			if (SDL_SetTextureAlphaMod(tOldImage, 252) != 0)
				//		if( SDL_SetTextureAlphaMod(tOldImage, 255) != 0 )
				break;
			if (SDL_RenderCopy(renderer, tOldImage, NULL, NULL) != 0)
				break;
			SDL_DestroyTexture(tOldImage);

		}

		// render all new new stuff
//		this->universe.render( renderer );
//		DisplayPlanets();
#if 1
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
#endif
		SDL_RenderPresent(renderer);
		return 0;				// Ok retun
	}
	printf("%s\n", SDL_GetError());
	#endif
	exit(1);		// Error return
}
#endif
