
#include <iostream>
#include <Windows.h>
#include "SDL.h"
#include "SDL_image.h"

// Return an SDL_Surface from SDLRenderer
// Please SDL_FreeSurface after use

//bool saveScreenshotBMP(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
SDL_Surface * saveScreenshotBMP( SDL_Window * SDLWindow, SDL_Renderer * SDLRenderer) {

    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(SDLWindow);
    if (infoSurface == NULL) {
        std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
    }
    else {
        unsigned char* pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels == 0) {
            std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
            return NULL;
        }
        else {
            if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format,
                pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
                std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
                delete[] pixels;
                return NULL;
            }
            else {
                saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h,
                    infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask,
                    infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);

                if (saveSurface == NULL) {
                    std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
                    delete[] pixels;
                    return NULL;
                }

//                SDL_FreeSurface(infoSurface);
//                delete[] pixels;    // maybe   todo
/*
                void * p = saveSurface->pixels;      // Just a test
                for (int i = 0; i < 3240000; i++) {
                    if (char c = ((char*)p)[i])
                        printf("%d %d\n", i, c );
                }
//*/
                return saveSurface;


#if 0
                SDL_SaveBMP(saveSurface, filepath.c_str());
                const char* p = SDL_GetError();
                SDL_FreeSurface(saveSurface);
                saveSurface = NULL;
#endif
            }
            delete[] pixels;    // todo
        }
        SDL_FreeSurface(infoSurface);
        infoSurface = NULL;
    }
    return NULL;
}