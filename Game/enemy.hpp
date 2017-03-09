#include "header.hpp"
//#include "entity.hpp"
#include <cstdlib>

class Enemy
{
public:
    Enemy(); //constructor
    ~Enemy() //destructor
    {

    }
    sf::Texture mEnemy;
    sf::Sprite mEnemySprite;

    void loadEnemyRandom(float x,float y); //loads the enemy randomly in the window
    void updateEnemy();

    bool loadEnemy; //boolean variable to check whether to draw enemy or not
private:
   float enemyLoadX; //sets the initial X position of enemy loading
   float enemyLoadY;

};
Enemy::Enemy():loadEnemy(false)
{
     if(!mEnemy.loadFromFile("resource/image/police.png"))
     {
         cout<<"Error in loading enemy spirit"<<endl;
     }
     mEnemySprite.setTexture(mEnemy);

}

void Enemy::loadEnemyRandom(float X,float Y)
{
   //enemyLoadX=rand()%800+20; //gives random values from 20 to 800
   enemyLoadX=X;
   enemyLoadY=Y;
   mEnemySprite.setPosition(enemyLoadX,enemyLoadY);

}

void Enemy::updateEnemy()
{
    if(loadEnemy==true)
    {
        enemyLoadY+=2*(0.7*1.56); //2 times the speed of background
        mEnemySprite.setPosition(enemyLoadX,enemyLoadY);
        if(enemyLoadY==650) //when enemy sprite reaches 650 y position then loading of sprite is terminated
            loadEnemy=false;
    }
}
