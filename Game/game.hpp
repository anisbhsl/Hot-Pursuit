#ifndef GAME
#define GAME

#include "header.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <cstring>
#include <sstream>

class Game
{
public:
    Game(); //game constructor
    void run();
    ~Game(){}  //game destructor

private:
    void processEvents();
    void update(float elapsedTime,int time);
    void render();

    sf::RenderWindow mWindow;
    sf::Texture mRoad;
    sf::Sprite  mRoadSprite1,mRoadSprite2;

    sf::Font scoreFont;
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

