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
    sf::Texture mEnemy, mBarrel;
    sf::Sprite mBarrelSprite;
    void loadEnemyRandom(float x,float y); //loads the enemy randomly in the window
    void loadBarrelRandom(float x,float y); //loads the barrel randomly in the window
    void updateEnemy(float bgSpeed);
    void updateBarrel(float bgSpeed);

    bool loadEnemy; //boolean variable to check whether to draw enemy or not
    bool loadBarrel; //boolean variable to check whether to draw barrel or not

private:
   float enemyLoadX; //sets the initial X position of enemy loading
   float enemyLoadY;

   float barrelLoadX; //sets the initial X position of barrel loading
   float barrelLoadY;

};

#endif // ENEMY

