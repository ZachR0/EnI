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
        //Object Types
        #define OBJECT_TYPE_UKN -1
        #define OBJECT_TYPE_SPRITE 0

        //TODO: Implement Object Types?

        //Object Class
        class Object
        {
        private:
            int ObjectType; //Object Type
            int xPos; //X Pos
            int yPos; //Y Pos
            int MoveSpeed; //Movement speed
            SpriteManager::Sprite *Sprite; //Object sprite
            bool Collision_Enabled; //Enable/disable collision detection
            bool Animate; //Enable/disable animation

            int object_index; //Index value for Current_Objects

        public:
            Object();
            Object(SpriteManager::Sprite *sprite, int x, int y, int speed, bool Collision);

            //Renders the Object
            void Render();

            //Object Animation Handle
            void Animation();

            //Object Movement Functions (Based on MoveSpeed)
            void MoveUp();
            void MoveDown();
            void MoveRight();
            void MoveLeft();

            //Gets X cord
            int getX();

            //Sets X Cord
            void setX(int x);

            //Gets Y cord
            int getY();

            //Sets Y Cord
            void setY(int y);

            //Sets Object's Cords Manually
            void setCords(int x, int y);

            //Returns MoveSpeed
            int getMoveSpeed();

            //Sets MoveSpeed
            void setMoveSpeed(int Speed);

            //Returns Animation status
            bool isAnimating();

            //Sets Animation status
            void setAnimating(bool status);

            //Returns Collision status
            bool isCollisionEnabled();

            //Sets Collision status
            void setCollision(bool status);

            //Gets the index
            int GetIndex();

            //Sets the index
            void SetIndex(int index);
        };

        //Dynamic Array of all Objects
        extern std::vector<Object> Current_Objects;
        extern int Current_Objects_Index; //Active index of Objects

       //Destroys an element
       void Destroy(int index);
    }
}


#endif
