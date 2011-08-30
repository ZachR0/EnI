#ifndef OBJECT_HEADER_FILE
#define OBJECT_HEADER_FILE

//CPP Headers
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>

//SDL Headers
#include <SDL.h>

//EnI Headers
#include "Sprites.h"

using namespace std;

//SDL Namespace
namespace SDL
{
    //Object Manager Namespace
    namespace ObjectManager
    {
        //Object Class
        class Object
        {
        private:
            int xPos;
            int yPos;
            int MoveSpeed;
            SpriteManager::Sprite Sprite;
            bool Collision_Enabled;


        };

        //Dynamic Array of all Objects
        extern std::vector<Object> Current_Objects;
        extern int Current_Objects_Index; //Active index of Objects

       //Destroys an element
       void Destroy(int index);
    }
}


#endif
