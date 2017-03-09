#include "player.hpp"

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

Player::Player():mIsMovingLeft(false),mIsMovingRight(false),playerScore("0"),Score(0)
{
    if(!mPlayer.loadFromFile("resource/image/audi.png")) //imports player
    {
        cout<<"No File found for player"<<endl;
    }
    mPlayerSprite.setTexture(mPlayer); //instantiates image as sprite
    mPlayerSprite.setPosition(positionX,positionY); //sets the position of sprite in the window
   //boundary conditions are (10,450) and (750,450)
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
     if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Player::updatePlayer()
{
    sf::Vector2f movement(0,0);
    sf::Vector2f playerPosition=mPlayerSprite.getPosition(); //gets the current position of our player

    if (mIsMovingLeft)
       if(playerPosition.x!=10) //checks whether left x position of our player is 10 or not
            movement.x-=1;
    if (mIsMovingRight)
        if(playerPosition.x!=750) //checks whether right x position of our player is 750 or not
            movement.x +=1;
    mPlayerSprite.move(movement);

}

int temp = 0;
void Player::updatePlayerScore(int elapsedTime)
{
    if( elapsedTime != temp )
    {
            Score+=5;
            playerScore = toString(Score);
            cout<< playerScore;
    }
    temp = elapsedTime;
}

