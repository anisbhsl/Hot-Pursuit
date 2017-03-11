#ifndef GAME
#define GAME

#include "header.hpp"
#include "player.hpp"
#include "enemy.hpp"


class Game
{
public:
    Game(); //game constructor
    void run();
    ~Game(){}  //game destructor
    void collision();
    void saveScore();

private:
    void processEvents();
    void update(float elapsedTime,int time);
    void render();

private:
    sf::RenderWindow mWindow;
    sf::Texture mRoad;
    sf::Sprite  mRoadSprite1,mRoadSprite2;

    sf::Font scoreFont,oFont;
    sf::Text scoreText,updateScoreText;

    Player player; //player object from Player class
    Enemy enemy; //enemy object from Enemy Class

    float diff;
    float bg1Y;
    float bg2Y;
    float bgSpeed;
    float elapsedTime;
};

#endif // GAME

