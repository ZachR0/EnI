#include "Events.h"


//SDL Events Namespace
namespace SDL
{
    namespace Events
    {
       //Handles SDL Events
        void Handle()
        {
            //SDL Event
            SDL_Event Event;

            //Reset Some Variables
            EventType = "";
            EventKey = "";

            //While there is an event to handle
            while(SDL_PollEvent(&Event))
            {
                //SDL Quit Event
                if (Event.type == SDL_QUIT)
                {
                    //Set the EventType
                    EventType = "sdl_quit";
                }

                //Keydown event
                if (Event.type == SDL_KEYDOWN)
                {
                    //Set the EventType
                    EventType = "keydown";

                    //Set the EventKey accordingly
                    switch(Event.key.keysym.sym)
                    {
                        case SDLK_UP: EventKey = "up"; break;
                        case SDLK_DOWN: EventKey = "down"; break;
                        case SDLK_LEFT: EventKey = "left"; break;
                        case SDLK_RIGHT: EventKey = "right"; break;
                        case SDLK_BACKSPACE: EventKey = "backspace"; break;
                        case SDLK_TAB: EventKey = "tab"; break;
                        case SDLK_LCTRL: EventKey = "left_control"; break;
                        case SDLK_RCTRL: EventKey = "right_control"; break;
                        case SDLK_LALT: EventKey = "left_alt"; break;
                        case SDLK_RALT: EventKey = "right_alt"; break;
                        case SDLK_SPACE: EventKey = "space"; break;
                        case SDLK_LSHIFT: EventKey = "left_shift"; break;
                        case SDLK_RSHIFT: EventKey = "right_shift"; break;
                        case SDLK_ESCAPE: EventKey = "escape"; break;
                        case SDLK_RETURN: EventKey = "enter"; break;
                        case SDLK_BACKQUOTE: EventKey = "backquote"; break;
                        case SDLK_UNKNOWN: EventKey = "unknown"; break;

                        default:
                            EventKey = (char)Event.key.keysym.unicode;
                            break;
                    }

                }

                //Keyup event
                if (Event.type == SDL_KEYUP)
                {
                    //Set the EventType
                    EventType = "keyup";

                    //Set the EventKey accordingly
                    switch(Event.key.keysym.sym)
                    {
                        case SDLK_UP: EventKey = "up"; break;
                        case SDLK_DOWN: EventKey = "down"; break;
                        case SDLK_LEFT: EventKey = "left"; break;
                        case SDLK_RIGHT: EventKey = "right"; break;
                        case SDLK_BACKSPACE: EventKey = "backspace"; break;
                        case SDLK_TAB: EventKey = "tab"; break;
                        case SDLK_LCTRL: EventKey = "left_control"; break;
                        case SDLK_RCTRL: EventKey = "right_control"; break;
                        case SDLK_LALT: EventKey = "left_alt"; break;
                        case SDLK_RALT: EventKey = "right_alt"; break;
                        case SDLK_SPACE: EventKey = "space"; break;
                        case SDLK_LSHIFT: EventKey = "left_shift"; break;
                        case SDLK_RSHIFT: EventKey = "right_shift"; break;
                        case SDLK_ESCAPE: EventKey = "escape"; break;
                        case SDLK_RETURN: EventKey = "enter"; break;
                        case SDLK_BACKQUOTE: EventKey = "backquote"; break;
                        case SDLK_UNKNOWN: EventKey = "unknown"; break;

                        default:
                            EventKey = (char)Event.key.keysym.unicode;
                            break;
                    }

                }
            }
        }

        //Gets the last event type that occured
        string GetEventType()
        {
            return EventType;
        }

        //Gets the last key press/release
        string GetKey()
        {
            return EventKey;
        }
    }
}
