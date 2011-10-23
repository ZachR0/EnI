#include "Object.h"
#include "Rendering.h"

using namespace std;

//SDL Namespace
namespace SDL
{
    //Object Manager Namespace
    namespace ObjectManager
    {
        //From Objects.h
        std::vector<Object> Current_Objects(1);
        int Current_Objects_Index = 1; //Active index of Objects

        Object::Object()
        {
            //Do nothing...
        }

        Object::Object(SpriteManager::Sprite *sprite, int x, int y, int speed, bool Collision)
        {
            //Setup Sprite Information
            this->Sprite = sprite;

            //Set other values
            this->xPos = x;
            this->yPos = y;
            this->MoveSpeed = speed;
            this->Collision_Enabled = Collision;
        }

        //Renders the Object
        void Object::Render()
        {
            SDL::Rendering::RenderSurface(this->Sprite->GetFrameSurface(this->Sprite->GetFrame()), SDL_GetVideoSurface(), this->xPos, this->yPos, NULL);
        }

        //Object Animation Handler
        void Object::Animation()
        {
            //Check if we should animate
            if(this->isAnimating())
            {
                //Enable Animation
                this->Sprite->SetAnimate(true);
            }
            else
            {
                //Disable Animation
                this->Sprite->SetAnimate(false);
            }
        }

        //Object Movement Functions (Based on MoveSpeed)
        void Object::MoveUp()
        {
            //Set Animation Direction
            this->Sprite->SetDirection(UP_DIRECTION);

            //Adjust cords accordingly
            this->setX(this->getY() - this->getMoveSpeed());
        }

        void Object::MoveDown()
        {
            //Set Animation Direction
            this->Sprite->SetDirection(DOWN_DIRECTION);

            //Adjust cords accordingly
            this->setX(this->getY() + this->getMoveSpeed());
        }

        void Object::MoveRight()
        {
            //Set Animation Direction
            this->Sprite->SetDirection(RIGHT_DIRECTION);

            //Adjust cords accordingly
            this->setX(this->getX() + this->getMoveSpeed());
        }

        void Object::MoveLeft()
        {
            //Set Animation Direction
            this->Sprite->SetDirection(LEFT_DIRECTION);

            //Adjust cords accordingly
            this->setX(this->getX() - this->getMoveSpeed());
        }

        //Gets X cord
        int Object::getX()
        {
            return this->xPos;
        }

        //Sets X Cord
        void Object::setX(int x)
        {
            this->xPos = x;
        }

        //Gets Y cord
        int Object::getY()
        {
            return this->yPos;
        }

        //Sets Y Cord
        void Object::setY(int y)
        {
            this->yPos = y;
        }

        //Sets Object's Cords Manually
        void Object::setCords(int x, int y)
        {
            this->xPos = x;
            this->yPos = y;
        }

        //Returns MoveSpeed
        int Object::getMoveSpeed()
        {
            return this->MoveSpeed;
        }

        //Sets MoveSpeed
        void Object::setMoveSpeed(int Speed)
        {
            this->MoveSpeed = Speed;
        }

        //Returns Animation status
        bool Object::isAnimating()
        {
            return this->Animate;
        }

        //Sets Animation status
        void Object::setAnimating(bool status)
        {
            this->Animate = status;
        }

        //Returns Collision status
        bool Object::isCollisionEnabled()
        {
            return this->Collision_Enabled;
        }

        //Sets Collision status
        void Object::setCollision(bool status)
        {
            this->Collision_Enabled = status;
        }

        //Sets the index
        void Object::SetIndex(int index)
        {
            this->object_index = index;
        }

        //Gets the index
        int Object::GetIndex()
        {
            return this->object_index;
        }

        //Destroys an element
        void Destroy(int index)
        {
            //Remove the element from the vector(dynamic array)
            Current_Objects.erase(Current_Objects.begin() + index);

            //Adjust our index
            Current_Objects_Index -= 1;
        }
    }
}
