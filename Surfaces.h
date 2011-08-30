#ifndef SURFACE_HEADER_FILE
#define SURFACE_HEADER_FILE

//CPP Headers
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

//SDL Headers
#include <SDL.h>

using namespace std;

//SDL Namespace
namespace SDL
{
    //Surface Management Namespace
    namespace SurfaceManagement
    {
        //All current surfaces
        extern std::vector<SDL_Surface*> Current_Surfaces;

        extern int Current_Surfaces_Index;

        //Class for surfaces
        class Surface
        {
            private:
            int surface_index; //Index value for Current_Surfaces

            //Sets the index
            void SetIndex(int index);

            public:
            //Loads Surface to Current_Surfaces - from image
            Surface(string image_file);

            //Loads Surface to Current_Surfaces - from SDL_Surface
            Surface(SDL_Surface *surf);

            //Gets the index
            int GetIndex();
        };


         //Returns an element of the vector
        SDL_Surface *GetElement(int index);

        //Destroys an element
        void Destroy(int index);

    }
}


#endif
