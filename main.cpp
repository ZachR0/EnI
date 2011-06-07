//CPP Headers
#include <iostream>
#include <fstream>
#include <algorithm>

//EnI Headers
#include "Config.h"
#include "Lua.h"

using namespace std;


//Variables from Config.h
string GAMELOC;
string GRAPHICS_LIB;

int main(int argc, char *argv[])
{
    //Display startup message
    cout << "EnI - Zach Rogers <zachrog@gmail.com> - Early Development Stages" << endl;
    cout << "----------------------------------------------------------------" << endl;

    //Get startup args to find out what game to load
    string Args = "";
    for(int i = 0; i < argc; i++)
    {
        Args += argv[i];
    }

    //Check for valid parameters
    int DashLoc = Args.find('-'); //Find "-"

    //Make sure parameter is present
    if(DashLoc > 0)
    {

        string GameLoc = Args.substr(DashLoc + 5); //Get everything after "-game "

        //Load configuration file
        string ConfigFileLoc = GameLoc + "/Game.config";
        string FileData = "";
        ifstream ConfigFile (ConfigFileLoc.c_str());

        //Make sure we can open the config file
        if (ConfigFile.is_open())
        {
            string LineData;

            //Read the file to EOF
            while (ConfigFile.good())
            {
                //Get next line
                getline (ConfigFile, LineData);

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

            //Close file
            ConfigFile.close();

            //Pull information from config file
            int GLibLoc = FileData.find("GLib"); //Find where GLib is being set
            string data = FileData.substr(GLibLoc + 4); //Remove data before GLib assignment
            remove(data.begin(), data.end(), ' '); //Remove spaces from data
            int EqualsLoc = data.find('='); //Find location of =
            data = data.substr(EqualsLoc + 1); //Set data to everything after the =
            int SemiLoc = data.find(';'); //Find the end of line semi-colon
            string GLibData = data.substr(0, SemiLoc); //The remaining data should be what we want

            //Check to make sure the GLib data is set to something that is valid
            if(GLibData != "SDL" && GLibData != "OpenGL")
            {
                cout << GLibData<< endl;
                cout << "[EnI]: Please check your configuration file GLib value, only SDL and OpenGL are supported!" << endl;
                return 0;
            }

            //Set Config Values
            GAMELOC = GameLoc;
            GRAPHICS_LIB = GLibData;

            //Init Lua
            LuaInterp::LuaInit();

            //Run Test Script
            string ScriptLoc = GameLoc + "/Game.lua";
            LuaInterp::RunScript(ScriptLoc.c_str(), false);


        }
        else
        {
            cout << "[EnI]: The game configuration file was not found for \"" << GameLoc << "\"!" << endl;
            return 0;
        }
    }
    else
    {
        cout << "[EnI]: You must specify the -game parameter!" << endl;
        return 0;
    }

    return 0;
}
