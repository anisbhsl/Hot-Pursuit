#ifndef ENEMY
#define ENEMY

#include "entity.hpp"
#include <cstdlib>

class Enemy : public Entity
{
public:
    Enemy(); //constructor
    ~Enemy() //destructor
    {

    }
    sf::Texture mEnemy;
    void loadEnemyRandom(float x,float y); //loads the enemy randomly in the window
    void updateEnemy();
    bool loadEnemy; //boolean variable to check whether to draw enemy or not

private:
   float enemyLoadX; //sets the initial X position of enemy loading
   float enemyLoadY;

};

#endif // ENEMY

