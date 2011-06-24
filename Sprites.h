//CPP Headers
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>

//SDL Headers
#include <SDL.h>

using namespace std;

//SDL Namespace
namespace SDL
{
    //Sprite Manager Namespace
    namespace SpriteManager
    {
        //Sprite Class
        class Sprite
        {
        private:
            //Sprite Information
            string SpriteSheet_Loc; //Location of Sprite/SpriteSheet
            string SpriteMap_Loc; //Location of Sprite Map

            //Animation type stuff
            bool isAnimating; //Should we animate?
            int MAX_FRAME; //Max frame in animation
            int Current_Frame; //Current frame in animation
            string Current_Direction; //Current direction for the animation to loop through (down, right, up, left)
            int *UpFrames; //Array of all the frames that are accociated with the Up direction animation
            int *DownFrames; //Array of all the frames that are accociated with the Down direction animation
            int *LeftFrames; //Array of all the frames that are accociated with the Left direction animation
            int *RightFrames; //Array of all the frames that are accociated with the Right direction animation
            SDL_Surface *Frames[]; //Frame Surface array

            int sprite_index; //Index value for Current_Sprites


        public:
            //Init - Loads SpriteSheet into memory accordingly, based on SpriteMap
            Sprite(string SpriteSheet, string SpriteMap);

            //Renders the Currect Frame
            void Render();

            //Renders a specific frame
            void Render(int Frame);

            //Animates - Handles the CurrentFrame
            void Animate();

            //Get the current frame
            int GetFrame();

            //Sets the current frame
            void SetFrame();

            //Get the maximum number of frames
            int GetMaxFrames();

            //Returns a specific frame as an SDL_Surface
            SDL_Surface *GetFrameSurface(int Frame);

            //Gets the index
            int GetIndex();

            //Sets the index
            void SetIndex(int index);

        };

        //Dynamic Array of all Sprite objects
        extern std::vector<Sprite*> Current_Sprites;
        extern int Current_Sprites_Index; //Active index of Sprite objects

       //Destroys an element
       void Destroy(int index);
    }
}
