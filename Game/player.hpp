#include "header.hpp"

class Player
{
public:
    Player(); //player constructor

    sf::Texture mPlayer;
    sf::Sprite mPlayerSprite;
    ~Player() //player destructor
    {

    }
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void updatePlayer();
    void updatePlayerScore(int elapsedTime);
    string playerScore;
    int Score;
private:

    float positionX=377.0; //x position of player
    float positionY=450.0;//y position of player
    float leftBoundX=10.0; //left boundary for player
    float rightBoundX=750.0; //right boundary for player

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

};

