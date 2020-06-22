#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

//Forward declaration
class GameManager;

class Bullet : public Entity
{
    public:
        Bullet(int x, int y, float xm, float ym, GameManager* gPtr, Entity* owner);

        //Pointer to entity that fired the bullet.
        Entity* firedBy = nullptr;
        void update();
    protected:

    private:
        //Direction of the bullet.
        sf::Vector2f vMov = sf::Vector2f(0,0);
};

#endif // BULLET_H
