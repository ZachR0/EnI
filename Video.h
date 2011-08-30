#ifndef VIDEO_HEADER_FILE
#define VIDEO_HEADER_FILE

//CPP Headers
#include <iostream>
#include <stdio.h>
#include <string.h>

//SDL Headers
#include <SDL.h>
#include <SDL_ttf/SDL_ttf.h>

using namespace std;

//SDL Namespace
namespace SDL
{
    //SDL Screen Surface
    static SDL_Surface *Screen = NULL;

    //Initializes SDL and it's subsystems
    bool Init(int Screen_Width, int Screen_Height, int Screen_BPP);

    //DeInitializes SDL and it's subsystems
    void DeInit();

    //Flips (refreshes) the SDL Screen
    void FlipDisplay();
}


#endif
