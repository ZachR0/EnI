#include "Sprites.h"
#include "Config.h"

//SDL Namespace
namespace SDL
{
    //Sprite Manager Namespace
    namespace SpriteManager
    {
        //From Sprites.h
        std::vector<SDL_Surface*> Current_Sprites(1);
        int Current_Sprites_Index = 1; //Active index of Sprite objects

        //Init - Loads SpriteSheet into memory accordingly, based on SpriteMap
        Sprite::Sprite(string SpriteSheet, string SpriteMap)
        {
            //Load SpriteMap File
            string FileLoc = GAMELOC + SpriteMap;
            string FileData = "";
            ifstream File (SpriteMap.c_str());

            //Make sure we can open the sprite map file
            if (File.is_open())
            {
                string LineData;

                //Read the file to EOF
                while (File.good())
                {
                    //Get next line
                    getline (File, LineData);

                    //Check for comments
                    if (LineData.substr(0,2) == "//")
                    {
                        //Do nothing, ignore the comment
                    }
                    else
                    {
                        //Add this line to the overall file data
                        FileData += LineData;
                    }
                }
              }
              else
              {

              }

            //Close file
            File.close();
        }

        //Renders the Currect Frame
        void Render()
        {

        }

        //Renders a specific frame
        void Render(int Frame)
        {

        }

        //Animates - Handles the CurrentFrame
        void Animate()
        {

        }

        //Get the current frame
        int GetFrame()
        {

        }

        //Sets the current frame
        void SetFrame()
        {

        }

        //Get the maximum number of frames
        int GetMaxFrames()
        {

        }

        //Returns a specific frame as an SDL_Surface
        SDL_Surface *GetFrameSurface(int Frame)
        {

        }
    }
}
