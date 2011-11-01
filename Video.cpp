#include "Video.h"
#include "Surfaces.h"
#include "FPS.h"

//SDL Namespace
namespace SDL
{
    //Initializes SDL and it's subsystems
    bool Init(int Screen_Width, int Screen_Height, int Screen_BPP)
    {
        //Initialize all SDL subsystems
        if(SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;

        //Setup the Screen
        Screen = SDL_SetVideoMode(Screen_Width, Screen_Height, Screen_BPP, SDL_SWSURFACE);

        //Make sure the screen setup went well
        if (Screen == NULL) return false;

        //Initialize FPS System
        SDL::FPS::Init(25);

        //Initialize SDL_ttf
        if(TTF_Init() == -1) return false;

        //Set the default window caption
        SDL_WM_SetCaption("EnI Engine", NULL);

        //Update the screen
        if(SDL_Flip(Screen) == -1) return false;

        //Enable Unicode
        SDL_EnableUNICODE( SDL_ENABLE );

        //Set Keyboard Input Delay
        SDL_EnableKeyRepeat(1, 1);

        //Assuming all went well..
        return true;
    }

    //DeInitializes SDL and it's subsystems
    void DeInit()
    {
        //Free All Surfaces from Surface Manager
        for (int index = 0; index < SDL::SurfaceManagement::Current_Surfaces_Index; index++)
        {
            //cout << "FreeSurf "<< index <<  " - " << SDL::SurfaceManagement::Current_Surfaces_Index << endl;
            try
            {
                //SDL_FreeSurface(SDL::SurfaceManagement::GetElement(index));
                SDL::SurfaceManagement::Destroy(index);
            }
            catch(...)
            {
                ; //Ignore
            }
        }

        //Disable Unicode
        SDL_EnableUNICODE( SDL_DISABLE );

        //Quit TTF
        TTF_Quit();

        //Quit SDL
        SDL_Quit();
    }

    //Flips (refreshes) the SDL Screen
    void FlipDisplay()
    {
        //Update the screen
        if(SDL_Flip(SDL_GetVideoSurface()) == -1)
        {
            cout << "[Lua]: There was a problem running SDL_Flip()!" << endl;
        }

        //Clear the screen
        SDL_FillRect(SDL_GetVideoSurface(), NULL, 0x000000);
    }

}
