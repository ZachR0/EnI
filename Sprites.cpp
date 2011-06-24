#include "Sprites.h"
#include "Config.h"

//SDL Namespace
namespace SDL
{
    //Sprite Manager Namespace
    namespace SpriteManager
    {
        //From Sprites.h
        std::vector<Sprite*> Current_Sprites(1);
        int Current_Sprites_Index = 1; //Active index of Sprite objects

        //Init - Loads SpriteSheet into memory accordingly, based on SpriteMap
        Sprite::Sprite(string SpriteSheet, string SpriteMap)
        {
            //Load SpriteMap File
            string FileLoc = GAMELOC + "/";
            FileLoc += SpriteMap;
            ifstream File (FileLoc.c_str());

            //Animation Stuff
            int Min_Frame_Up = -1;
            int Max_Frame_Up = 0;

            int Min_Frame_Down = -1;
            int Max_Frame_Down = 0;

            int Min_Frame_Right = -1;
            int Max_Frame_Right = 0;

            int Min_Frame_Left = -1;
            int Max_Frame_Left = 0;

            //Make sure we can open the sprite map file
            if (File.is_open())
            {
                string LineData;

                //Read the file to EOF
                int count = 0; //Keeps track of loop count, for frame assignment
                while (File.good())
                {
                    //Clear any old data
                    LineData = "";

                    //Get next line
                    getline (File, LineData);

                    //Check for comments
                    if (LineData.substr(0,1) == "#")
                    {
                        //Do nothing, ignore the comment
                    }
                    else
                    {
                        //Get the direction
                        int Sep_Loc = LineData.find(';');
                        string Direction = LineData.substr(0, Sep_Loc);
                        LineData = LineData.substr(Sep_Loc+1); //Remove old data

                        cout << "[SpriteManager]: Direction in SpriteMap:" << Direction << endl;

                        //Get the OffsetX
                        Sep_Loc = LineData.find(';');
                        string OffX = LineData.substr(0, Sep_Loc);
                        LineData = LineData.substr(Sep_Loc+1); //Remove old data

                        cout << "[SpriteManager]: OffX in SpriteMap:" << OffX << endl;

                        //Get the OffsetY
                        Sep_Loc = LineData.find(';');
                        string OffY = LineData.substr(0, Sep_Loc);
                        LineData = LineData.substr(Sep_Loc+1); //Remove old data

                        cout << "[SpriteManager]: OffY in SpriteMap:" << OffY << endl;

                        //Get the Width
                        Sep_Loc = LineData.find(';');
                        string Width = LineData.substr(0, Sep_Loc);
                        LineData = LineData.substr(Sep_Loc+1); //Remove old data

                        cout << "[SpriteManager]: Width in SpriteMap:" << Width << endl;

                        //Get the Height
                        Sep_Loc = LineData.find(';');
                        string Height = LineData.substr(0, Sep_Loc);

                        cout << "[SpriteManager]: Height in SpriteMap:" << Height << endl;

                        //Animation Frame Assignment
                        if (Direction == "DOWN")
                        {
                            //Set the Min Frame?
                            if (Min_Frame_Down == -1)
                            {
                                Min_Frame_Down = count;
                            }

                            //Update the Max Frame
                            Max_Frame_Down += 1;
                        }
                        else if (Direction == "UP")
                        {
                            //Set the Min Frame?
                            if (Min_Frame_Up == -1)
                            {
                                Min_Frame_Up = count;
                            }

                            //Update the Max Frame
                            Max_Frame_Up += 1;
                        }
                        else if (Direction == "RIGHT")
                        {
                            //Set the Min Frame?
                            if (Min_Frame_Right == -1)
                            {
                                Min_Frame_Right = count;
                            }

                            //Update the Max Frame
                            Max_Frame_Right += 1;
                        }
                        else if (Direction == "LEFT")
                        {
                            //Set the Min Frame?
                            if (Min_Frame_Left == -1)
                            {
                                Min_Frame_Left = count;
                            }

                            //Update the Max Frame
                            Max_Frame_Left += 1;
                        }

                        //Increase loop count
                        count += 1;
                    }
                }

                //Close file
                File.close();

                //Fix Max Frame Values
                Max_Frame_Down += Min_Frame_Down;
                Max_Frame_Up += Min_Frame_Up;
                Max_Frame_Right += Min_Frame_Right;
                Max_Frame_Left += Min_Frame_Left;

                //Take the Max Frame values down one to respect the "starting from zero" system
                Max_Frame_Down -= 1;
                Max_Frame_Up -= 1;
                Max_Frame_Right -= 1;
                Max_Frame_Left -= 1;


                //Output Framing Assignments
                cout << "DOWN: Min " << Min_Frame_Down << " ; Max " << Max_Frame_Down << " ; Total Frames " << (Max_Frame_Down - Min_Frame_Down) << endl;
                cout << "UP: Min " << Min_Frame_Up << " ; Max " << Max_Frame_Up << " ; Total Frames " << (Max_Frame_Up - Min_Frame_Up) << endl;
                cout << "RIGHT: Min " << Min_Frame_Right << " ; Max " << Max_Frame_Right << " ; Total Frames " << (Max_Frame_Right - Min_Frame_Right) << endl;
                cout << "LEFT: Min " << Min_Frame_Left << " ; Max " << Max_Frame_Left << " ; Total Frames " << (Max_Frame_Left - Min_Frame_Left) << endl;

                //Get Directional Frame Totals
                int Total_Frames_Down = (Max_Frame_Down - Min_Frame_Down) + 1;
                int Total_Frames_Up = (Max_Frame_Up - Min_Frame_Up) + 1;
                int Total_Frames_Right = (Max_Frame_Right - Min_Frame_Right) + 1;
                int Total_Frames_Left = (Max_Frame_Left - Min_Frame_Left) + 1;

                //Resize frame animation arrays
                this->DownFrames = new int[Total_Frames_Down]();
                this->UpFrames = new int[Total_Frames_Up]();
                this->RightFrames = new int[Total_Frames_Right]();
                this->LeftFrames = new int[Total_Frames_Left]();

                //Pass each directional frame assignement value to the frame animation arrays
                int index = 0;
                for(int i = Min_Frame_Down; i < Max_Frame_Down; i++)
                {
                    this->DownFrames[index] = i;
                }

                index = 0;
                for(int i = Min_Frame_Up; i < Max_Frame_Up; i++)
                {
                    this->UpFrames[index] = i;
                    index++;
                }

                index = 0;
                for(int i = Min_Frame_Right; i < Max_Frame_Right; i++)
                {
                    this->RightFrames[index] = i;
                    index++;
                }

                index = 0;
                for(int i = Min_Frame_Left; i < Max_Frame_Left; i++)
                {
                    this->LeftFrames[index] = i;
                    index++;
                }

                //TODO: Add code that will actually load each frame subimage into memory -- SDL_Surface* galore! xD
              }

              else
              {
                  //Issue opening file
                  cout << "[SpriteManager]: Are you sure the sprite map \"" << FileLoc << "\" exists?" << endl;
              }
        }

        //Renders the Currect Frame
        void Sprite::Render()
        {

        }

        //Renders a specific frame
        void Sprite::Render(int Frame)
        {

        }

        //Animates - Handles the CurrentFrame
        void Sprite::Animate()
        {

        }

        //Get the current frame
        int Sprite::GetFrame()
        {

        }

        //Sets the current frame
        void Sprite::SetFrame()
        {

        }

        //Get the maximum number of frames
        int Sprite::GetMaxFrames()
        {

        }

        //Returns a specific frame as an SDL_Surface
        SDL_Surface *Sprite::GetFrameSurface(int Frame)
        {

        }

        //Sets the index
        void Sprite::SetIndex(int index)
        {
            this->sprite_index = index;
        }

        //Gets the index
        int Sprite::GetIndex()
        {
            return this->sprite_index;
        }

        //Destroys an element
        void Destroy(int index)
        {
            //Remove the element from the vector(dynamic array)
            Current_Sprites.erase(Current_Sprites.begin() + index);

            //Adjust our index
            Current_Sprites_Index -= 1;
        }
    }
}
