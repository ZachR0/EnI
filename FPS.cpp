#include "FPS.h"

//SDL Namespace
namespace SDL
{
    //FPS Namespace
    namespace FPS
    {
        //FPS Timer
        Timer FPS_Timer;

        //Current FPS
        int CURRENT_FPS = 25; //Default FPS

        Timer::Timer()
        {
            //Initialize the variables
            startTicks = 0;
            pausedTicks = 0;
            paused = false;
            started = false;
        }

        void Timer::start()
        {
            //Start the timer
            started = true;

            //Unpause the timer
            paused = false;

            //Get the current clock time
            startTicks = SDL_GetTicks();
        }

        void Timer::stop()
        {
            //Stop the timer
            started = false;

            //Unpause the timer
            paused = false;
        }

        void Timer::pause()
        {
            //If the timer is running and isn't already paused
            if( ( started == true ) && ( paused == false ) )
            {
                //Pause the timer
                paused = true;

                //Calculate the paused ticks
                pausedTicks = SDL_GetTicks() - startTicks;
            }
        }

        void Timer::unpause()
        {
            //If the timer is paused
            if( paused == true )
            {
                //Unpause the timer
                paused = false;

                //Reset the starting ticks
                startTicks = SDL_GetTicks() - pausedTicks;

                //Reset the paused ticks
                pausedTicks = 0;
            }
        }

        int Timer::get_ticks()
        {
            //If the timer is running
            if( started == true )
            {
                //If the timer is paused
                if( paused == true )
                {
                    //Return the number of ticks when the timer was paused
                    return pausedTicks;
                }
                else
                {
                    //Return the current time minus the start time
                    return SDL_GetTicks() - startTicks;
                }
            }

            //If the timer isn't running
            return 0;
        }

        bool Timer::is_started()
        {
            return started;
        }

        bool Timer::is_paused()
        {
            return paused;
        }


        //Initialize FPS stuff
        void Init(int FPS)
        {
            //Set FPS
            CURRENT_FPS = FPS;

            //Start the FPS timer
            FPS_Timer.start();
        }

        //Delays to keep FPS capped, if needed
        void Check()
        {
            //If we want to cap the frame rate
            if( ( FPS_Timer.get_ticks() < 1000 / CURRENT_FPS ) )
            {
                //Sleep the remaining frame time
                SDL_Delay( ( 1000 / CURRENT_FPS ) - FPS_Timer.get_ticks() );

                //Restart the FPS timer
                FPS_Timer.stop();
                FPS_Timer.start();
            }
        }
    }
}
