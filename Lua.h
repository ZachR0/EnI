#ifndef LUA_HEADER_FILE
#define LUA_HEADER_FILE

//CPP Headers
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <pthread.h>


//Lua Headers
extern "C" {
        #include <Lua/5.1.4_osx/include/lua.h>
        #include <Lua/5.1.4_osx/include/lualib.h>
        #include <Lua/5.1.4_osx/include/lauxlib.h>
}

//SDL Headers
#include <SDL.h>

using namespace std;

//Lua Interpreter Namespace
namespace LuaInterp
{
    //The actual Lua Interpreter
    static lua_State *Interpreter;

    //Initializes Lua
    bool LuaInit();

    //Used by RunScript() for running scripts in a new thread
    void *_Run_Script(void* ptr);

    //Runs Lua Scripts
    void RunScript(string script, bool new_thread);

    //DeInitializes Lua
    void LuaDeInit();

}

//Lua Functions Namespace (Functions for Lua)
namespace LuaFunctions
{
    //Initializes SDL/OpenGL
    static int Init(lua_State *L);

    //DeInitializes SDL/OpenGL
    static int DeInit(lua_State *L);

    //Flips (refreshes) the SDL/OpenGL screen
    static int Screen_Flip(lua_State *L);

    //Handles Events
    static int Event_Handle(lua_State *L);

    //Gets the most recent event type to occur
    static int Event_GetType(lua_State *L);

    //Gets the most recent key press/release to occur
    static int Event_GetKey(lua_State *L);

    //Loads an image as an SDL_Surface into the SurfaceManagement System
    static int LoadImage(lua_State *L);

    //Renders a Surface via SurfaceManagement
    static int Render_Surface(lua_State *L);

    //Renders TTF text to an SDL_Surface into the SurfaceManagement system
    static int Generate_Text(lua_State *L);

    //Destroys an instance of a Surface in the SurfaceManagement System
    static int SurfaceManagement_Destroy(lua_State *L);

    //Loads a TTF into the TTFManagement System
    static int LoadTTF(lua_State *L);

    //Destroys an instance of a TTF_Font in the TTFManagement System
    static int TTFManagement_Destroy(lua_State *L);

    //Initalizes a new Sprite object for the SpriteManager
    static int SpriteManager_Init(lua_State *L);

    //Animates a Sprite object from the SpriteManager
    static int SpriteManager_Animation(lua_State *L);

    //Renders a Sprite object from the SpriteManager
    static int SpriteManager_Render(lua_State *L);

    //Sets the direction for Animation for a Sprite object from the SpriteManager
    static int SpriteManager_SetDirection(lua_State *L);

    //Enables Sprite Animation
    static int SpriteManager_AnimationEnable(lua_State *L);

    //Disables Sprite Animation
    static int SpriteManager_AnimationDisable(lua_State *L);

    //Initalizes a new Object manager object
    static int ObjectManager_Init(lua_State *L);

    //Renders an object from the object manager
    static int ObjectManager_Render(lua_State *L);

    //Checks FPS and delays if needed
    static int FPS_Check(lua_State *L);

    //Sets FPS
    static int FPS_Set(lua_State *L);
}

#endif
