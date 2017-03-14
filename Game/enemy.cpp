#include "enemy.hpp"

Enemy::Enemy():loadEnemy(false)
{
     if(!mEnemy.loadFromFile("resource/image/police.png"))
     {
         cout<<"Error in loading enemy spirit"<<endl;
     }
     eSprite.setTexture(mEnemy);
     movementSpeed = 1.1;

     if(!mBarrel.loadFromFile("resource/image/barrel.png"))
     {
         cout<<"Error in loading barrel"<<endl;
     }
     mBarrelSprite.setTexture(mBarrel);


}

void Enemy::loadEnemyRandom(float X,float Y)
{
   enemyLoadX=X;
   enemyLoadY=Y;
   eSprite.setPosition(enemyLoadX,enemyLoadY);

}

void Enemy::loadBarrelRandom(float X,float Y)
{
    barrelLoadX=X;
    barrelLoadY=Y;
    mBarrelSprite.setPosition(barrelLoadX,barrelLoadY);
}

void Enemy::updateEnemy(float bgSpeed)
{
    if(loadEnemy==true)
    {
        enemyLoadY+=movementSpeed*(bgSpeed); //movementSpeed times the speed of background
        eSprite.setPosition(enemyLoadX,enemyLoadY);
        if(enemyLoadY==700) //when enemy sprite reaches 700 y position then loading of sprite is terminated
            loadEnemy=false;
    }

}
void Enemy::updateBarrel(float bgSpeed)
{
  if(loadBarrel==true)
    {
        barrelLoadY+=bgSpeed;
        mBarrelSprite.setPosition(barrelLoadX,barrelLoadY);
        if(barrelLoadY==700) //when barrel sprite reaches 700 y position then loading of sprite is terminated
            loadBarrel=false;

    }
}

