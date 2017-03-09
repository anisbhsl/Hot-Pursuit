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




Game ::Game() : mWindow(sf::VideoMode(900,642), "Hot-Pursuit"), //size of game window is 900 x 642 pixels
    mRoad(),mRoadSprite1(),mRoadSprite2(),player()
{
    mWindow.setPosition(sf::Vector2i(177,0)); //sets the position of gaming window in screen
    bgSpeed=0.7;
    if(!mRoad.loadFromFile("resource/image/roadb.png")) //imports road texture
    {
        cout<<"No File found for road"<<endl;
    }
    mRoad.setSmooth(true);

    mRoadSprite1.setTexture(mRoad); //instantiates image as sprite
    mRoadSprite1.setPosition(0,0);  //sets the position of gaming environment in window
    bg1Y=mRoadSprite1.getPosition().y; //gets the y position of road sprite 1

    mRoadSprite2.setTexture(mRoad);
    mRoadSprite2.setPosition(0,-642); //sets the position of gaming environment in window
    bg2Y=mRoadSprite1.getPosition().y; //gets the y position of road sprite 2


    ////////////////////////////////////Sound////////////////////////////////////////////////////////////

 /*   if(!buffer.loadFromFile("resource/sounds/policesiren.ogg"))
    {
        cout<<"No File found for police siren"<<endl;
    }
    mSiren.setBuffer(buffer);
    mSiren.setLoop(true); //loops the sound
*/

    /////////////////////////////////Score ///////////////////////////////////////////////////////////////
    if(!scoreFont.loadFromFile("resource/fonts/arial.ttf"))
        cout<<"Error Loading score font"<<endl;
    scoreText.setFont(scoreFont);
    scoreText.setString("Score:");
    scoreText.setCharacterSize(30);
    scoreText.setPosition(420,10);
    scoreText.setStyle(sf::Text::Bold); //sets the text style bold

    updateScoreText.setFont(scoreFont);
    updateScoreText.setString(player.playerScore);
    updateScoreText.setCharacterSize(30);
    updateScoreText.setPosition(520,10);
    updateScoreText.setStyle(sf::Text::Bold);//sets the text style bold
}

void Game::run()
{

    //mSiren.play();
    sf::Clock clock; //starts the clock

    while (mWindow.isOpen())

    {

        processEvents();

        sf::Time playTime=clock.getElapsedTime();
        int ptime=(playTime.asMilliseconds()/1000);

        float x=rand()%750+20; //gives range of values from 750 to 20
        if((ptime%2==0)) //after each 2 seconds the enemy is generated randomly
        {
            enemy.loadEnemyRandom(x,-250);
            enemy.loadEnemy=true;
        }
        update(elapsedTime=1.32,ptime);
        render();

    }
}
void Game::processEvents()  //handles user events
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            player.handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            player.handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::update(float elapsedTime,int time)   //updates the entities in the game
{
    diff=bg1Y-mWindow.getSize().y; //calculates the difference between y-position of backround and y-size of window

    if(bg1Y>=640)
    {
        bg1Y=-638;
    }
    else
    {
        bg1Y+=bgSpeed*elapsedTime;
    }
    if(bg2Y>=mWindow.getSize().y)
    {
        bg2Y=-640;
    }
    else if(bg2Y<bg1Y)
    {
        bg2Y=diff+5;
    }
    else
    {
        bg2Y+=bgSpeed*elapsedTime; //y position is changed
    }
    mRoadSprite1.setPosition(0,bg1Y); //sets the position of road sprite
    mRoadSprite2.setPosition(0,bg2Y); //sets the position of road sprite
    //////////////collison/////////////////
    if (player.mPlayerSprite.getGlobalBounds().intersects(enemy.mEnemySprite.getGlobalBounds())) //collison detection
    {
        mWindow.close(); //game window closes when collison occurs
    }
    else
    {
        player.updatePlayer(); //updates the player movement with user input
        player.updatePlayerScore(time);
        updateScoreText.setString(player.playerScore);
    }

    if(enemy.loadEnemy==true) //whenever loadEnemy variable holds true value, enemy position is updated
        enemy.updateEnemy();

}

void Game::render()  //renders the game
{
    mWindow.clear();
    mWindow.draw(mRoadSprite1); //draws road
    mWindow.draw(mRoadSprite2); //draws road
    mWindow.draw(player.mPlayerSprite); //draws the car(player)
    mWindow.draw(scoreText); //shows Score string
    mWindow.draw(updateScoreText); //updates score in the screen
    if(enemy.loadEnemy==true)
        mWindow.draw(enemy.mEnemySprite); //draws the enemy sprite
    mWindow.display();
}




