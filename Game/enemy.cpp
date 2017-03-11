#include "enemy.hpp"

Enemy::Enemy():loadEnemy(false)
{
     if(!mEnemy.loadFromFile("resource/image/police.png"))
     {
         cout<<"Error in loading enemy spirit"<<endl;
     }
     eSprite.setTexture(mEnemy);
     movementSpeed = 0.9;

}

void Enemy::loadEnemyRandom(float X,float Y)
{
   //enemyLoadX=rand()%800+20; //gives random values from 20 to 800
   enemyLoadX=X;
   enemyLoadY=Y;
   eSprite.setPosition(enemyLoadX,enemyLoadY);

}

void Enemy::updateEnemy()
{
    if(loadEnemy==true)
    {
        enemyLoadY+=movementSpeed*(0.7*1.56); //movementSpeed times the speed of background
        eSprite.setPosition(enemyLoadX,enemyLoadY);
        if(enemyLoadY==650) //when enemy sprite reaches 650 y position then loading of sprite is terminated
            loadEnemy=false;
    }
}

