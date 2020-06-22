#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"


//Forward declaration of GameManager class
class GameManager;

//Enemy class, the red squares that fire bullets at the player.
class Enemy : public Entity
{
    public:
        Enemy(int x, int y, GameManager* gm);
        virtual ~Enemy();
        void update();

    protected:

    private:
        //Same as player the Enemy can only fire two bullets per second.
        sf::Clock firingClock;
};

#endif // ENEMY_H
