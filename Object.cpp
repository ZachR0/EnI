#include "Object.h"

using namespace std;

//SDL Namespace
namespace SDL
{
    //Object Manager Namespace
    namespace ObjectManager
    {
        //From Objects.h
        std::vector<Object> Current_Objects(1);
        int Current_Objects_Index = 1; //Active index of Objects

       //Destroys an element
       void Destroy(int index)
       {
           //Remove the element from the vector(dynamic array)
           Current_Objects.erase(Current_Objects.begin() + index);

           //Adjust our index
           Current_Objects_Index -= 1;
       }
    }
}
