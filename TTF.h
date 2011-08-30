#ifndef TTF_HEADER_FILE
#define TTF_HEADER_FILE

//CPP Headers
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

//SDL Headers
#include <SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>

using namespace std;

//SDL Namespace
namespace SDL
{
    //TTFManagement Namespace
    namespace TTFManagement
    {
        //All current TTF
        extern std::vector<TTF_Font*> Current_TTF;

        extern int Current_TTF_Index;

        //Class for true type fonts
        class Font
        {
            private:
            int surface_index; //Index value for Current_TTF

            //Sets the index
            void SetIndex(int index);

            public:
            //Loads the ttf_gile to Current_TTF
            Font(string ttf_file, int size);

            //Gets the index
            int GetIndex();
        };


         //Returns an element of the vector
        TTF_Font *GetElement(int index);

        //Destroys an element
        void Destroy(int index);
    }
}


#endif
