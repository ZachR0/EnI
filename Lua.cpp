#include "Lua.h"
#include "Video.h"
#include "Events.h"
#include "Rendering.h"
#include "Surfaces.h"
#include "Config.h"
#include "TTF.h"
#include "Sprites.h"
#include "FPS.h"
#include "Object.h"

//Lua Interpreter Namespace
namespace LuaInterp
{
    //Initializes Lua
    bool LuaInit()
    {
        //Attempt to Initialize Lua awesomeness!
        try
        {
            //Initialize Lua
            Interpreter = lua_open();

            //Load Lua base libraries
            luaL_openlibs(Interpreter);

            //Register Lua Functions
            lua_register(Interpreter, "Init", LuaFunctions::Init);
            lua_register(Interpreter, "DeInit", LuaFunctions::DeInit);
            lua_register(Interpreter, "Screen_Flip", LuaFunctions::Screen_Flip);
            lua_register(Interpreter, "Event_Handle", LuaFunctions::Event_Handle);
            lua_register(Interpreter, "Event_GetType", LuaFunctions::Event_GetType);
            lua_register(Interpreter, "Event_GetKey", LuaFunctions::Event_GetKey);
            lua_register(Interpreter, "Load_Image", LuaFunctions::LoadImage);
            lua_register(Interpreter, "Render_Surface", LuaFunctions::Render_Surface);
            lua_register(Interpreter, "Generate_Text", LuaFunctions::Generate_Text);
            lua_register(Interpreter, "SurfDestroy", LuaFunctions::SurfaceManagement_Destroy);
            lua_register(Interpreter, "Load_TTF", LuaFunctions::LoadTTF);
            lua_register(Interpreter, "TTFDestroy", LuaFunctions::TTFManagement_Destroy);
            lua_register(Interpreter, "Sprite", LuaFunctions::SpriteManager_Init);
            lua_register(Interpreter, "Sprite_Animate", LuaFunctions::SpriteManager_Animation);
            lua_register(Interpreter, "Sprite_Render", LuaFunctions::SpriteManager_Render);
            lua_register(Interpreter, "Sprite_SetDirection", LuaFunctions::SpriteManager_SetDirection);
            lua_register(Interpreter, "Sprite_AnimateEnable", LuaFunctions::SpriteManager_AnimationEnable);
            lua_register(Interpreter, "Sprite_AnimateDisable", LuaFunctions::SpriteManager_AnimationDisable);
            lua_register(Interpreter, "Object", LuaFunctions::ObjectManager_Init);
            lua_register(Interpreter, "Object_Render", LuaFunctions::ObjectManager_Render);
            lua_register(Interpreter, "Object_Animate", LuaFunctions::ObjectManager_Animate);
            lua_register(Interpreter, "Object_MoveUp", LuaFunctions::ObjectManager_MoveUp);
            lua_register(Interpreter, "Object_MoveDown", LuaFunctions::ObjectManager_MoveDown);
            lua_register(Interpreter, "Object_MoveRight", LuaFunctions::ObjectManager_MoveRight);
            lua_register(Interpreter, "Object_MoveLeft", LuaFunctions::ObjectManager_MoveLeft);
            lua_register(Interpreter, "Object_GetX", LuaFunctions::ObjectManager_GetX);
            lua_register(Interpreter, "Object_SetX", LuaFunctions::ObjectManager_SetX);
            lua_register(Interpreter, "Object_GetY", LuaFunctions::ObjectManager_GetY);
            lua_register(Interpreter, "Object_SetY", LuaFunctions::ObjectManager_SetY);
            lua_register(Interpreter, "Object_SetCords", LuaFunctions::ObjectManager_SetCords);
            lua_register(Interpreter, "Object_GetSpeed", LuaFunctions::ObjectManager_GetMoveSpeed);
            lua_register(Interpreter, "Object_SetSpeed", LuaFunctions::ObjectManager_SetMoveSpeed);
            lua_register(Interpreter, "Object_GetAnimStatus", LuaFunctions::ObjectManager_GetAnimStatus);
            lua_register(Interpreter, "Object_SetAnimStatus", LuaFunctions::ObjectManager_SetAnimStatus);
            lua_register(Interpreter, "Object_GetCollisionStatus", LuaFunctions::ObjectManager_GetCollisionStatus);
            lua_register(Interpreter, "Object_SetCollisionStatus", LuaFunctions::ObjectManager_SetCollisionStatus);
            lua_register(Interpreter, "FPS_Check", LuaFunctions::FPS_Check);
            lua_register(Interpreter, "FPS_Set", LuaFunctions::FPS_Set);

        }
        catch(...)
        {
            cout << "[Lua]: Initial Init failed." << endl;
            return false;
        }

        //Assuming that all went well...
        return true;
    }

    //Used by RunScript() for running scripts in a new thread
    void *_Run_Script(void* ptr)
    {
        //Pull the script file from the parameter passed
        char *script_file;
        script_file = (char *) ptr;

        //Run Script
        luaL_dofile(Interpreter, script_file);
    }

    //Runs Lua Scripts
    void RunScript(string script, bool new_thread)
    {
        //Threads, pl0x?
        if (new_thread)
        {
            //Our Thread
            pthread_t Script_Thread;

            //Create and run our thread
            pthread_create(&Script_Thread, NULL, _Run_Script, (void*) script.c_str());

            //Wait for terminiation of existing threads
            pthread_join(Script_Thread, NULL);

        }
        else
        {
            //Run the script
            luaL_dofile(Interpreter, script.c_str());
        }

    }


    //DeInitializes Lua
    void LuaDeInit()
    {
        //Cleanup Lua
        lua_close(Interpreter);
    }

}

//Lua Functions Namespace (Functions for Lua)
namespace LuaFunctions
{
    //Initializes SDL/OpenGL
    static int Init(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Catch any issues
            try
            {
                //Get the Width argument
                int Width = lua_tonumber(LuaInterp::Interpreter, 1);

                //Get the Height argument
                int Height = lua_tonumber(LuaInterp::Interpreter, 2);

                //Get the BPP argument
                int BPP = lua_tonumber(LuaInterp::Interpreter, 3);

                //Check parameters
                if ((Width > 0) && (Height > 0) && (BPP > 0))
                {
                    //Call SDL Init
                    SDL::Init(Width, Height, BPP);
                }
                else
                {
                    //Throw an error
                    throw "ERROR-PARAMETERS";
                }
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem running SDL_Init! Please check your parameters!" << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Init()" << endl;
        }
    }

    //DeInitializes SDL/OpenGL
    static int DeInit(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Call SDL DeInit
            SDL::DeInit();
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function DeInit()" << endl;
        }
    }

    //Flips (refreshes) the SDL/OpenGL screen
    static int Screen_Flip(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Call SDL Flip Display
            SDL::FlipDisplay();
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Screen_Flip()" << endl;
        }
    }

    //Handles Events
    static int Event_Handle(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            SDL::Events::Handle();
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Event_Handle()" << endl;
        }
    }

    //Gets the most recent event type to occur
    static int Event_GetType(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Return the event type
            string event_type = SDL::Events::GetEventType();
            lua_pushstring(L, event_type.c_str());

            return 1;
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Event_GetType()" << endl;
        }
    }

    //Gets the most recent key press/release to occur
    static int Event_GetKey(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Return the key
            string event_key = SDL::Events::GetKey();
            lua_pushstring(L, event_key.c_str());

            return 1;
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Event_GetKey()" << endl;
        }
    }

    //Loads and image as an SDL_Surface into the SurfaceManagement System
    static int LoadImage(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            string ImageFile = "";

            //Catch and issues
            try
            {
                //Get the image file parameter
                string ImageFiletmp = lua_tostring(LuaInterp::Interpreter, 1);

                //Add the full path onto the given parameter
                ImageFile = GAMELOC;
                ImageFile += "/" + ImageFiletmp;
                //cout << ImageFile << endl;

                //Check paramter
                if ((ImageFile != ""))
                {
                    //Create a new SurfaceManagement Surface and load the ImageFile
                    SDL::SurfaceManagement::Surface Surf = SDL::SurfaceManagement::Surface(ImageFile);

                    //Get the Surface index
                    int index = Surf.GetIndex();

                    //Return the index
                    lua_pushnumber(L, index);

                    return 1;
                }
                else
                {
                    throw "ERROR-PARAMETERS";
                }
            }
            catch(...)
            {
                cout << "[Lua]: There was an error loading your image \"" << ImageFile << "\"! Does the image exist?" << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Load_Image()" << endl;
        }

    }


    //Renders a Surface via SurfaceManagement
    static int Render_Surface(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            int SurfIndex = lua_tonumber(LuaInterp::Interpreter, 1);
            int xPos = lua_tonumber(LuaInterp::Interpreter, 2);
            int yPos = lua_tonumber(LuaInterp::Interpreter, 3);

            SDL::Rendering::RenderSurface(SDL::SurfaceManagement::GetElement(SurfIndex), SDL_GetVideoSurface(), xPos, yPos, NULL);
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Render_Surface()" << endl;
        }

    }

    //Renders TTF text to an SDL_Surface into the SurfaceManagement system
    static int Generate_Text(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            string Text = "";
            int FontIndex = 0;
            int FontSize = 0;
            int FR = 0; //Foreground Color Red
            int FG = 0; //Foreground Color Green
            int FB = 0; //Foreground Color Blue


            //Catch and issues
            try
            {
                //Get parameters
                Text = lua_tostring(LuaInterp::Interpreter, 1); //Get the Text parameter
                FontIndex = lua_tonumber(LuaInterp::Interpreter, 2); //Get the font location
                FR = lua_tonumber(LuaInterp::Interpreter, 3); //Get the R color
                FG = lua_tonumber(LuaInterp::Interpreter, 4); //Get the G color
                FB = lua_tonumber(LuaInterp::Interpreter, 5); //Get the B color

                SDL_Color fcolor = {FR, FG, FB};
                SDL_Surface *FontSurf = SDL::Rendering::GenerateText(Text, fcolor, SDL::TTFManagement::GetElement(FontIndex));

                //Create a new SurfaceManagement Surface and load the Generated Text Surface
                SDL::SurfaceManagement::Surface Surf = SDL::SurfaceManagement::Surface(FontSurf);

                //Get the Surface index
                int index = Surf.GetIndex();

                Surf = NULL;

                //Return the index
                lua_pushnumber(L, index);

                return 1;
            }
            catch(...)
            {
                cout << "[Lua]: There was a Loading your font! Was the instance destroyed? [" << FontIndex << "]" << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Generate_Text()" << endl;
        }
    }

    //Destroys an instance of a Surface in the SurfaceManagement System
    static int SurfaceManagement_Destroy(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get parameters
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            SDL::SurfaceManagement::Destroy(index);
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function SurfDestroy()" << endl;
        }
    }

    //Loads a TTF into the TTFManagement System
    static int LoadTTF(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            string TTFFile = "";

            //Catch and issues
            try
            {
                //Get the ttf file parameter
                string TTFFiletmp = lua_tostring(LuaInterp::Interpreter, 1);

                //Add the full path onto the given parameter
                TTFFile = GAMELOC;
                TTFFile += "/" + TTFFiletmp;

                //Get the ttf size parameter
                int TTFSize = lua_tonumber(LuaInterp::Interpreter, 2);

                //Check paramter
                if ((TTFFile != ""))
                {
                    //Create a new TTFManagement TTF
                    SDL::TTFManagement::Font Font = SDL::TTFManagement::Font(TTFFile, TTFSize);

                    //Get the Surface index
                    int index = Font.GetIndex();

                    //Return the index
                    lua_pushnumber(L, index);

                    return 1;
                }
                else
                {
                    throw "ERROR-PARAMETERS";
                }
            }
            catch(...)
            {
                cout << "[Lua]: There was an error loading your font \"" << TTFFile << "\"! Does the file exist?" << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function Load_TTF()" << endl;
        }
    }

    //Destroys an instance of a TTF_Font in the TTFManagement System
    static int TTFManagement_Destroy(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get parameters
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            SDL::TTFManagement::Destroy(index);
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua function TTFDestroy()" << endl;
        }
    }

    //Initalizes a new Sprite object for the SpriteManager
    static int SpriteManager_Init(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get parameters
            string SpriteSheet = lua_tostring(LuaInterp::Interpreter, 1);
            string SpriteMap = lua_tostring(LuaInterp::Interpreter, 2);


            //Init our Sprite
            SDL::SpriteManager::Sprite tmpSprite = SDL::SpriteManager::Sprite(SpriteSheet, SpriteMap);

            //Resize our dynamic array (vector)
            SDL::SpriteManager::Current_Sprites.resize(SDL::SpriteManager::Current_Sprites.size() + 1); //Buffer an extra element

            //Set Index that this sprite obj is located at in Current_Sprites array
            tmpSprite.SetIndex(SDL::SpriteManager::Current_Sprites_Index);

            //Load our sprite obj
            SDL::SpriteManager::Current_Sprites.at(SDL::SpriteManager::Current_Sprites_Index) = tmpSprite;

            //Incrase Index
            SDL::SpriteManager::Current_Sprites_Index++;

            //Get the Sprite index
            int index = tmpSprite.GetIndex();

            //Return the index
            lua_pushnumber(L, index);

            return 1;
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Sprite()" << endl;
        }
    }

    //Animates a Sprite object from the SpriteManager
    static int SpriteManager_Animation(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get Sprite ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Call Animate function
            try
            {
                SDL::SpriteManager::Current_Sprites.at(index).Animate();
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Sprite_Animate function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Sprite_Animate()" << endl;
        }

        return 0;

    }

    //Renders a Sprite object from the SpriteManager
    static int SpriteManager_Render(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get Sprite ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Get Render X,Y
            int x = lua_tonumber(LuaInterp::Interpreter, 2);
            int y = lua_tonumber(LuaInterp::Interpreter, 3);

            //Call Render function
            try
            {
                SDL::SpriteManager::Current_Sprites.at(index).Render(x, y);
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Sprite_Render function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Sprite_Render()" << endl;
        }

        return 0;

    }

    //Sets the direction for Animation for a Sprite object from the SpriteManager
    static int SpriteManager_SetDirection(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get Sprite ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Get Direction
            string direction = lua_tostring(LuaInterp::Interpreter, 2);
            int new_direction = UNK_DIRECTION;

            //Convert direction to something the SetDirection function will understand
            if (direction == "up")
            {
                new_direction = UP_DIRECTION;
            }
            else if (direction == "down")
            {
                new_direction = DOWN_DIRECTION;
            }
            else if (direction == "left")
            {
                new_direction = LEFT_DIRECTION;
            }
            else if (direction == "right")
            {
                new_direction = RIGHT_DIRECTION;
            }

            //Call Set Direction function
            try
            {
                SDL::SpriteManager::Current_Sprites.at(index).SetDirection(new_direction);
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Sprite_SetDirection function for obj " << index <<  " - Valid directions up, down, left, right" << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Sprite_SetDirection()" << endl;
        }

        return 0;
    }

    //Enables Sprite Animation
    static int SpriteManager_AnimationEnable(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get Sprite ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Enable Animation
            try
            {
                SDL::SpriteManager::Current_Sprites.at(index).SetAnimate(true);
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Sprite_AnimateEnable function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Sprite_AnimateEnable()" << endl;
        }

        return 0;
    }

    //Disables Sprite Animation
    static int SpriteManager_AnimationDisable(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get Sprite ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Disable Animation
            try
            {
                SDL::SpriteManager::Current_Sprites.at(index).SetAnimate(false);
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Sprite_AnimateDisable function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Sprite_AnimateDisable()" << endl;
        }

        return 0;
    }

    //Initalizes a new Object manager object
    static int ObjectManager_Init(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get parameters
            int SpriteManager_Index = lua_tonumber(LuaInterp::Interpreter, 1);
            int x = lua_tonumber(LuaInterp::Interpreter, 2);
            int y = lua_tonumber(LuaInterp::Interpreter, 3);
            int speed = lua_tonumber(LuaInterp::Interpreter, 4);
            int collision = lua_tonumber(LuaInterp::Interpreter, 5);

            //Init our Object
            SDL::ObjectManager::Object tmpObject = SDL::ObjectManager::Object(&SDL::SpriteManager::Current_Sprites.at(SpriteManager_Index), x, y, speed, collision);

            //Resize our dynamic array (vector)
            SDL::ObjectManager::Current_Objects.resize(SDL::ObjectManager::Current_Objects.size() + 1); //Buffer an extra element

            //Set Index that this Object Manager obj is located at in Current_Objects array
            tmpObject.SetIndex(SDL::ObjectManager::Current_Objects_Index);

            //Load our obj
            SDL::ObjectManager::Current_Objects.at(SDL::ObjectManager::Current_Objects_Index) = tmpObject;

            //Increase Index
            SDL::ObjectManager::Current_Objects_Index++;

            //Get the Object index
            int index = tmpObject.GetIndex();

            //Return the index
            lua_pushnumber(L, index);

            return 1;
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object()" << endl;
        }

        return 0;
    }

    //Renders an object from the object manager
    static int ObjectManager_Render(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Call Render function
            try
            {
                SDL::ObjectManager::Current_Objects.at(index).Render();
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_Render function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_Render()" << endl;
        }

        return 0;
    }

    //Animates an object from the object manager
    static int ObjectManager_Animate(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Call the Animation function
            try
            {
                SDL::ObjectManager::Current_Objects.at(index).Animation();
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_Animate function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_Animate()" << endl;
        }

        return 0;
    }

    //Object Movement - Up Direction
    static int ObjectManager_MoveUp(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Simply call the MoveUP Function
            try
            {
                SDL::ObjectManager::Current_Objects.at(index).MoveUp();
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_MoveUp function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_MoveUp()" << endl;
        }

        return 0;
    }

    //Object Movement - Down Direction
    static int ObjectManager_MoveDown(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Simply call the MoveDown Function
            try
            {
                SDL::ObjectManager::Current_Objects.at(index).MoveDown();
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_MoveDown function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_MoveDown()" << endl;
        }


        return 0;
    }

    //Object Movement - Right Direction
    static int ObjectManager_MoveRight(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Simply call the MoveRight Function
            try
            {
                SDL::ObjectManager::Current_Objects.at(index).MoveRight();
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_MoveRight function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_MoveRight()" << endl;
        }


        return 0;
    }

    //Object Movement - Left Direction
    static int ObjectManager_MoveLeft(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Simply call the MoveLeft Function
            try
            {
                SDL::ObjectManager::Current_Objects.at(index).MoveLeft();
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_MoveLeft function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_MoveLeft()" << endl;
        }


        return 0;
    }

    //Get the x cord from an object in the Object Manager
    static int ObjectManager_GetX(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            try
            {
                //Get the Obj X
                int x = SDL::ObjectManager::Current_Objects.at(index).getX();

                //Return the data
                lua_pushnumber(L, x);

                return 1;
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_GetX function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_GetX()" << endl;
        }


        return 0;
    }

    //Sets the x cord of an object in the Object Manager
    static int ObjectManager_SetX(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Get other parameters
            int x = lua_tonumber(LuaInterp::Interpreter, 2);

            try
            {
                //Set the Obj X
                SDL::ObjectManager::Current_Objects.at(index).setX(x);

            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_SetX function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_SetX()" << endl;
        }

        return 0;
    }

    //Get the y cord from an object in the Object Manager
    static int ObjectManager_GetY(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            try
            {
                //Get the Obj Y
                int y = SDL::ObjectManager::Current_Objects.at(index).getY();

                //Return the data
                lua_pushnumber(L, y);

                return 1;
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_GetY function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_GetY()" << endl;
        }


        return 0;
    }

    //Sets the Y cord of an object in the Object Manager
    static int ObjectManager_SetY(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Get other parameters
            int y = lua_tonumber(LuaInterp::Interpreter, 2);

            try
            {
                //Set the Obj Y
                SDL::ObjectManager::Current_Objects.at(index).setY(y);

            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_SetY function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_SetY()" << endl;
        }

        return 0;
    }

    //Sets the X,Y cords of an object in the Object Manager
    static int ObjectManager_SetCords(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Get other parameters
            int x = lua_tonumber(LuaInterp::Interpreter, 2);
            int y = lua_tonumber(LuaInterp::Interpreter, 3);

            try
            {
                //Set the Obj X
                SDL::ObjectManager::Current_Objects.at(index).setX(x);

                //Set the Obj Y
                SDL::ObjectManager::Current_Objects.at(index).setY(y);

            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_SetCords function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_SetCords()" << endl;
        }

        return 0;
    }

    //Gets the move speed of an object in the Object Manager
    static int ObjectManager_GetMoveSpeed(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            try
            {
                //Get the Obj Speed
                int speed = SDL::ObjectManager::Current_Objects.at(index).getMoveSpeed();

                //Return the data
                lua_pushnumber(L, speed);

                return 1;
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_GetMoveSpeed function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_GetMoveSpeed()" << endl;
        }


        return 0;
    }

    //Sets the move speed of an object in the Object Manager
    static int ObjectManager_SetMoveSpeed(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Get other parameters
            int speed = lua_tonumber(LuaInterp::Interpreter, 2);

            try
            {
                //Set the Obj Speed
                SDL::ObjectManager::Current_Objects.at(index).setMoveSpeed(speed);

            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_SetMoveSpeed function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_SetMoveSpeed()" << endl;
        }

        return 0;

    }

    //Gets the animation status of an object in the Object Manager
    static int ObjectManager_GetAnimStatus(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            try
            {
                //Get the Obj Animation Status
                bool status = SDL::ObjectManager::Current_Objects.at(index).isAnimating();

                //Set return val
                int val = 0;
                switch(status)
                {
                case true:
                    val = 1;
                    break;
                case false:
                    val = 0;
                    break;
                default:
                    val = -1;
                    break;
                };

                //Return the data
                lua_pushnumber(L, val);

                return 1;
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_GetAnimStatus function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_GetAnimStatus()" << endl;
        }


        return 0;
    }

    //Sets the animation status of an object in the Object Manager
    static int ObjectManager_SetAnimStatus(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Get other parameters
            int status = lua_tonumber(LuaInterp::Interpreter, 2);

            try
            {
                //Set the Obj Animation Status
                bool newStatus = false;
                if(status == 1) newStatus = true;
                if(status == 0) newStatus = false;
                SDL::ObjectManager::Current_Objects.at(index).setAnimating(newStatus);

            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_SetAnimStatus function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_SetAnimStatus()" << endl;
        }

        return 0;
    }

    //Gets the collision status(enabled/disabled) of an Object in the Object Manager
    static int ObjectManager_GetCollisionStatus(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            try
            {
                //Get the Obj Collision Status
                bool status = SDL::ObjectManager::Current_Objects.at(index).isCollisionEnabled();

                //Set return val
                int val = 0;
                switch(status)
                {
                case true:
                    val = 1;
                    break;
                case false:
                    val = 0;
                    break;
                default:
                    val = -1;
                    break;
                };

                //Return the data
                lua_pushnumber(L, val);

                return 1;
            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_GetCollisionStatus function for obj " << index << endl;
            }

        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_GetCollisionStatus()" << endl;
        }


        return 0;
    }

    //Sets  the collision status(enable/disable) of an Object in the Object Manager
    static int ObjectManager_SetCollisionStatus(lua_State *L)
    {
        //SDL
        if(GRAPHICS_LIB == "SDL")
        {
            //Get Object ID
            int index = lua_tonumber(LuaInterp::Interpreter, 1);

            //Get other parameters
            int status = lua_tonumber(LuaInterp::Interpreter, 2);

            try
            {
                //Set the Obj Collision Status
                bool newStatus = false;
                if(status == 1) newStatus = true;
                if(status == 0) newStatus = false;
                SDL::ObjectManager::Current_Objects.at(index).setCollision(newStatus);

            }
            catch(...)
            {
                cout << "[Lua]: There was a problem accessing the Object_SetCollisionStatus function for obj " << index << endl;
            }
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function Object_SetCollisionStatus()" << endl;
        }

        return 0;
    }

    //Checks FPS and delays if needed
    static int FPS_Check(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Check and delay if needed
            SDL::FPS::Check();
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function FPS_Check()" << endl;
        }

        return 0;
    }

    //Sets FPS
    static int FPS_Set(lua_State *L)
    {
        //SDL
        if (GRAPHICS_LIB == "SDL")
        {
            //Get new FPS
            int fps = lua_tonumber(LuaInterp::Interpreter, 1);

            //ReInit the FPS system
            SDL::FPS::Init(fps);
        }

        //OpenGL
        else if(GRAPHICS_LIB == "OpenGL")
        {
            cout << "[EnI]: OpenGL currently is not supported for the Lua Function FPS_Set()" << endl;
        }

        return 0;
    }
}
