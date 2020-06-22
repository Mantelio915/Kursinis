#ifndef ASTEROID_
#define ASTEROID_
#include "Entity.h"

//Forward declaration
class GameManager;
class Asteroid : public Entity
{
    public:
        Asteroid(int x, int y, GameManager* gPtr);
        //Pointer to game manager object pointer
        GameManager* gP = nullptr;
        void update();


    protected:

    private:
};

#endif // ASTEROID_
