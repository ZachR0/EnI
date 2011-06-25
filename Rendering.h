//CPP Headers
#include <iostream>
#include <stdio.h>
#include <string.h>

//SDL Headers
#include <SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>

using namespace std;

//SDL Namespace
namespace SDL
{
    //Rendering Namespace
    namespace Rendering
    {
        //Loads image file into memory
        SDL_Surface *Load_Image(string imagefile);

        //Directly renders an image (SDL_Surface) to a surface
        //Blits src to dest at x,y - clip would be the offsets for the src surface
        bool RenderSurface(SDL_Surface* src, SDL_Surface *dest, int x, int y, SDL_Rect* clip);

        //Returns a subimage (clipped area) of another SDL_Surface as a SDL_Surface
        SDL_Surface *GetSubImage(SDL_Surface *surf, SDL_Rect* clip);

        //Geneterates Text to an SDL_Surface
        SDL_Surface *GenerateText(string Text, SDL_Color ForegroundColor, TTF_Font *Font);
    }
}
