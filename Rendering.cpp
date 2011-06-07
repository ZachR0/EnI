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

