#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

//Forward declaration
class GameManager;


//The player class
class Player : public Entity
{
    public:
        Player(int x, int y, GameManager* gmanagerP);
        void update();
        virtual ~Player();

        //Pointer to the GameManager object
        GameManager* gP = nullptr;

        //The health points of the player
        int health = 100;

    protected:

    private:
        //SFML clock to control the firerate of player, locked to two bullets per second
        sf::Clock firingClock;

};

#endif // PLAYER_H
