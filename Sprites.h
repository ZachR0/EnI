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
    //Sprite Manager Namespace
    namespace SpriteManager
    {
        //Dynamic Array of all Sprite objects
        extern std::vector<SDL_Surface*> Current_Sprites;
        extern int Current_Sprites_Index; //Active index of Sprite objects

        //Sprite Class
        class Sprite
        {
        private:
            //Sprite Information
            string SpriteSheet_Loc; //Location of Sprite/SpriteSheet
            string SpriteMap_Loc; //Location of Sprite Map

            //Animation type stuff
            bool Animate; //Should we animate?
            int MAX_FRAME; //Max frame in animation
            int Current_Frame; //Current frame in animation
            SDL_Surface *Frames[]; //Frame Surface array

        public:
            Sprite(string SpriteSheet, string SpriteMap);

        };
    }
}
