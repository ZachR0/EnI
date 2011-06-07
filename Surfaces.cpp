#include "Surfaces.h"
#include "Rendering.h"

//SDL Namespace
namespace SDL
{
    //Surface Management Namespace
    namespace SurfaceManagement
    {
        //From Surfaces.h
        std::vector<SDL_Surface*> Current_Surfaces(1);
        int Current_Surfaces_Index = 1;

        //Loads Surface - from image
        Surface::Surface(string image_file)
        {
            //Resize our dynamic array (vector)
            Current_Surfaces.resize(Current_Surfaces.size() + 1); //Buffer an extra element

            //Load our surface
            Current_Surfaces.at(Current_Surfaces_Index) = SDL::Rendering::Load_Image(image_file);

            //Set Index that this surface is located at in Current_Surfaces
            this->SetIndex(Current_Surfaces_Index);

            //Incrase Index
            Current_Surfaces_Index++;

        }

        //Loads Surface to Current_Surfaces - from SDL_Surface
        Surface::Surface(SDL_Surface *surf)
        {
            //Resize our dynamic array (vector)
            Current_Surfaces.resize(Current_Surfaces.size() + 1); //Buffer an extra element

            //Load our surface
            Current_Surfaces.at(Current_Surfaces_Index) = surf;

            //Set Index that this surface is located at in Current_Surfaces
            this->SetIndex(Current_Surfaces_Index);

            //Incrase Index
            Current_Surfaces_Index++;
        }

         //Sets the index
        void Surface::SetIndex(int index)
        {
            this->surface_index = index;
        }

        //Gets the index
        int Surface::GetIndex()
        {
            return this->surface_index;
        }

        //Returns an element of the vector
        SDL_Surface *GetElement(int index)
        {
            return Current_Surfaces.at(index);
        }

         //Destroys an element
        void Destroy(int index)
        {
            //Free the SDL Surface
            SDL_FreeSurface(Current_Surfaces.at(index));

            //Remove the element from the vector
            Current_Surfaces.erase(Current_Surfaces.begin() + index);

            //Adjust our index
            Current_Surfaces_Index -= 1;
        }
    }
}
