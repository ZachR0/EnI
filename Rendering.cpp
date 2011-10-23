#include "Rendering.h"

//SDL Namespace
namespace SDL
{
    //Rendering Namespace
    namespace Rendering
    {
        //Loads image file into memory
        SDL_Surface *Load_Image(string imagefile)
        {
            //The image that's loaded
            SDL_Surface* loadedImage = NULL;

            //The optimized image that will be used
            SDL_Surface* optimizedImage = NULL;

            //Load the image using SDL_image
            loadedImage = IMG_Load( imagefile.c_str() );

            //If the image loaded
            if( loadedImage != NULL )
            {
                //Create an optimized image
                optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

                //Free the old image
                SDL_FreeSurface( loadedImage );
            }

            //Return the optimized image
            return optimizedImage;
        }

        //Directly renders an image (SDL_Surface) to a surface
        bool RenderSurface(SDL_Surface* src, SDL_Surface *dest, int x, int y, SDL_Rect* clip)
        {
            //Make sure that our source surface is valid
            if (src != NULL)
            {
                //Make a temporary rectangle to hold the offsets
                SDL_Rect offset;

                //Give the offsets to the rectangle
                offset.x = x;
                offset.y = y;

                //Blit the surface
                SDL_BlitSurface(src, clip, dest, &offset);
            }
            else
            {
                return false;
            }

            //Assuming that all went well..
            return true;
        }

        //Returns a subimage (clipped area) of another SDL_Surface as a SDL_Surface
        SDL_Surface *GetSubImage(SDL_Surface *surf, SDL_Rect* clip)
        {
            //RBGA Masks
            Uint32 rmask, gmask, bmask, amask;

            //SDL interprets each pixel as a 32-bit number, so our masks must depend on the endianness (byte order) of the machine
            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
                rmask = 0xff000000;
                gmask = 0x00ff0000;
                bmask = 0x0000ff00;
                amask = 0x000000ff;
            #else
                rmask = 0x000000ff;
                gmask = 0x0000ff00;
                bmask = 0x00ff0000;
                amask = 0xff000000;
            #endif

            //Create our 32bit surface for blitting
            SDL_Surface *sub = SDL_CreateRGBSurface(SDL_SWSURFACE, clip->w, clip->h, 32, rmask, gmask, bmask, amask);

            //Create a copy of our source image to clip from
            SDL_Surface *tmp = SDL_DisplayFormatAlpha(surf);

            //Set Alpha accordingly
            SDL_SetAlpha(tmp, 0, 0);

            //Blit our clipped tmp surface to sub
            SDL_BlitSurface(tmp, clip, sub, NULL);

            //Garbage Collection FTW
            SDL_FreeSurface(tmp);

            //Return our subimage
            return sub;
        }

        //Geneterates Text to an SDL_Surface
        SDL_Surface *GenerateText(string Text, SDL_Color ForegroundColor, TTF_Font *Font)
        {
            SDL_Surface *TextSurf = NULL;

            if ((TextSurf = TTF_RenderText_Solid(Font, Text.c_str(), ForegroundColor)) == NULL)
            {
                    cout << "[EnI]: There was a problem rendering your text" << endl;
            }

            return TextSurf;
        }
    }
}

