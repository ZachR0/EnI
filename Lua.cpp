#include "Lua.h"
#include "Video.h"
#include "Events.h"
#include "Rendering.h"
#include "Surfaces.h"
#include "Config.h"
#include "TTF.h"

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

            cout << GAMELOC << endl;

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
                cout << ImageFile << endl;

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
        //Get parameters
        int index = lua_tonumber(LuaInterp::Interpreter, 1);

        SDL::SurfaceManagement::Destroy(index);
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
        //Get parameters
        int index = lua_tonumber(LuaInterp::Interpreter, 1);

        SDL::TTFManagement::Destroy(index);
    }
}
