#ifndef EVENTS_HEADER_FILE
#define EVENTS_HEADER_FILE

//CPP Headers
#include <iostream>
#include <stdio.h>
#include <string.h>

//SDL Headers
#include <SDL.h>

using namespace std;

//SDL Events Namespace
namespace SDL
{
    namespace Events
    {
        static string EventType; //Holds the last event type to occur
        static string EventKey; //Holds the last key to be pressed / released

        //Handles SDL Events
        void Handle();

        //Gets the last event type that occured
        string GetEventType();

        //Gets the last key press/release
        string GetKey();
    }
}


#endif
