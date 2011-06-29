//CPP Headers
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

//SDL Headers
#include <SDL.h>

using namespace std;

//SDL Namespace
namespace SDL
{
    //FPS Namespace
    namespace FPS
    {
        //Timer Class
        class Timer
        {
        private:
            //The clock time when the timer started
            int startTicks;

            //The ticks stored when the timer was paused
            int pausedTicks;

            //The timer status
            bool paused;
            bool started;

        public:
            //Initializes variables
            Timer();

            //The various clock actions
            void start();
            void stop();
            void pause();
            void unpause();

            //Gets the timer's time
            int get_ticks();

            //Checks the status of the timer
            bool is_started();
            bool is_paused();
        };

        //FPS Timer
        extern Timer FPS_Timer;

        //Current FPS
        extern int CURRENT_FPS;

        //Initialize FPS stuff
        void Init(int FPS);

        //Delays to keep FPS capped, if needed
        void Check();
    }
}
