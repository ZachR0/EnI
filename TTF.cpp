#include "TTF.h"

//SDL Namespace
namespace SDL
{
    //TTFManagement Namespace
    namespace TTFManagement
    {
        //From TTF.h
        std::vector<TTF_Font*> Current_TTF(1);
        int Current_TTF_Index = 1;

        //Loads Surface - from image
        Font::Font(string ttf_file, int size)
        {
            //Resize our dynamic array (vector)
            Current_TTF.resize(Current_TTF.size() + 1); //Buffer an extra element

            //Load our surface
            Current_TTF.at(Current_TTF_Index) = TTF_OpenFont(ttf_file.c_str(), size);

            //Set Index that this surface is located at in Current_Surfaces
            this->SetIndex(Current_TTF_Index);

            //Increase Index
            Current_TTF_Index++;

        }

        //Sets the index
        void Font::SetIndex(int index)
        {
            this->surface_index = index;
        }

        //Gets the index
        int Font::GetIndex()
        {
            return this->surface_index;
        }

        //Returns an element of the vector
        TTF_Font *GetElement(int index)
        {
            return Current_TTF.at(index);
        }

         //Destroys an element
        void Destroy(int index)
        {
            //Remove Element
            //delete Current_TTF[index]; (Current_TTF.erase should do this already)

            //Remove the element from the vector
            Current_TTF.erase(Current_TTF.begin() + index);

            //Adjust our index
            Current_TTF_Index -= 1;
        }
    }
}
