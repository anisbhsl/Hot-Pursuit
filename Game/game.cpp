#include "game.hpp"

int StringToInteger(string NumberAsString)
{
	int NumberAsInteger;
	stringstream ss;
	ss << NumberAsString;
	ss >> NumberAsInteger;
	return NumberAsInteger;
}

template <typename T>
string ToString(T val)
{
    stringstream stream;
    stream << val;
    return stream.str();
}

Game ::Game() : mWindow(sf::VideoMode(900,642), "Hot-Pursuit"), //size of game window is 900 x 642 pixels
    mRoad(),mRoadSprite1(),mRoadSprite2(),player(),oFont(),previousScore(0)
{
    mWindow.setPosition(sf::Vector2i(177,0)); //sets the position of gaming window in screen
    bgSpeed=0.8;
    if(!mRoad.loadFromFile("resource/image/roadb.png")) //imports road texture
    {
        cout<<"No File found for road"<<endl;
    }
    mRoad.setSmooth(true);

    mRoadSprite1.setTexture(mRoad);         //instantiates image as sprite
    mRoadSprite1.setPosition(0,0);          //sets the position of gaming environment in window
    bg1Y=mRoadSprite1.getPosition().y;      //gets the y position of road sprite 1

    mRoadSprite2.setTexture(mRoad);
    mRoadSprite2.setPosition(0,-642);       //sets the position of gaming environment in window
    bg2Y=mRoadSprite1.getPosition().y;      //gets the y position of road sprite 2


    if(!oFont.loadFromFile("resource/fonts/PatrioticNepal_rabinsxp.ttf"))
        cout<<"Error Loading menu font"<<endl;

    ////////////////////////////////////Sound////////////////////////////////////////////////////////////

      if(!buffer.loadFromFile("resource/sounds/policesiren.ogg"))
           cout<<"No File found for police siren"<<endl;
       mSiren.setBuffer(buffer);
       mSiren.setLoop(true); //loops the sound

        if(!buffer1.loadFromFile("resource/sounds/shatter.ogg"))
           cout<<"No File found for police siren"<<endl;
       mShatter.setBuffer(buffer1);


    /////////////////////////////////Score ///////////////////////////////////////////////////////////////


    if(!scoreFont.loadFromFile("resource/fonts/leafy.otf"))
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
    mSiren.play();        //game sound play
    sf::Clock clock;        //starts clock

    while (mWindow.isOpen())
    {
        processEvents();

        sf::Time playTime=clock.getElapsedTime();
        int ptime=(playTime.asMilliseconds()/1000);  //converts the time in milliseconds to seconds

        float x=rand()%750+20;  //gives range of values from 750 to 20
        if((ptime%3==0))        //after each 2 seconds the enemy is generated randomly
        {
            if((ptime%5!=0))
            {
                enemy.loadEnemyRandom(x,-250);
                enemy.loadEnemy=true;
            }
        }
        if((ptime%5==0))
        {
            enemy.loadBarrelRandom(x,-250);
            enemy.loadBarrel=true;
        }
        update(elapsedTime=0.7,ptime);
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
    diff=bg1Y-mWindow.getSize().y; //calculates the difference between y-position of background and y-size of window

    if(bg1Y>=640)
        bg1Y=-638;
    else
        bg1Y+=bgSpeed*elapsedTime;
    if(bg2Y>=mWindow.getSize().y)
        bg2Y=-640;
    else if(bg2Y<bg1Y)
        bg2Y=diff+5;
    else
        bg2Y+=bgSpeed*elapsedTime;      //y position is changed


    mRoadSprite1.setPosition(0,bg1Y);   //sets the position of road sprite
    mRoadSprite2.setPosition(0,bg2Y);   //sets the position of road sprite

    //////////////collison/////////////////
    if (player.eSprite.getGlobalBounds().intersects(enemy.eSprite.getGlobalBounds())) //collison detection with police car
    {
        collision();
        saveScore();
        mWindow.close();        //game window closes when collison occurs
    }
    else if(player.eSprite.getGlobalBounds().intersects(enemy.mBarrelSprite.getGlobalBounds())) //collision detection with barrel
    {
        collision();
        saveScore();
        mWindow.close();
    }
    else
    {
        player.updatePlayer();  //updates the player movement with user input
        player.updatePlayerScore(time);
        updateScoreText.setString(player.playerScore);
    }

    //Level UP
    if( previousScore% 100 == 0 && previousScore != player.Score)
        bgSpeed+=0.3;

    previousScore = player.Score;

    if(enemy.loadEnemy==true) //whenever loadEnemy variable holds true value, enemy position is updated
        enemy.updateEnemy(bgSpeed);
    if(enemy.loadBarrel==true)
    {
        enemy.updateBarrel(bgSpeed); //whenever loadBarrel variable holds true value, barrel position is updated
    }



}

void Game::render()  //renders the game
{
    mWindow.clear();
    mWindow.draw(mRoadSprite1); //draws road
    mWindow.draw(mRoadSprite2); //draws road
    mWindow.draw(player.eSprite); //draws the car(player)
    mWindow.draw(scoreText); //shows Score string
    mWindow.draw(updateScoreText); //updates score in the screen
    if(enemy.loadEnemy==true)
        mWindow.draw(enemy.eSprite); //draws the enemy sprite
    if(enemy.loadBarrel==true)
        mWindow.draw(enemy.mBarrelSprite);
    mWindow.display();
}

void Game::collision()
{
    mSiren.stop();
    mShatter.play();
    sf::Text gameOver;
    gameOver.setFont(oFont);
    gameOver.setCharacterSize(127);
    string s = "Game Over";
    string sub;
    //gameOver.setString(s);
    sf::Vector2f v;
    v.x = (mWindow.getSize().x)/8;
    v.y = (mWindow.getSize().y)/3;
    gameOver.setPosition(sf::Vector2f(v));

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0,0,0,77));
    rect.setSize(sf::Vector2f(mWindow.getSize()));

    for(int i = 0 ; i != s.length()+1; i++)
    {
        sub.append(s,i,1);
        gameOver.setString(sub);
        mWindow.draw(rect);
        mWindow.draw(gameOver);
        mWindow.display();
        Sleep(200);
    }
    sf::Text scoreDisplay;
    scoreDisplay.setFont(scoreFont);
    string score = "Your Score " + player.playerScore;
    scoreDisplay.setCharacterSize(77);
    scoreDisplay.setPosition(sf::Vector2f(mWindow.getSize().x/10,mWindow.getSize().y/1.5));
    scoreDisplay.setString(score);
    mWindow.draw(scoreDisplay);
    mWindow.display();
    Sleep(3700);
}

void Game::saveScore()
{
    fstream scorefile;
    scorefile.open("score.txt",ios::in);
    if(!scorefile)
    {
        cout<<"error1"<<endl;
    }
    static int i=0,length,position;
    string scores[100];
    while(!scorefile.eof())
    {
        scorefile>>scores[i];
        //cout<<scores[i]<<endl;
        length=i+1;
        i++;
    }
    //cout<<length<<endl;
    scorefile.close();

    scores[length-1]=player.playerScore;

    //convert scores to integer type to sort as integer
    int intscore[length];
    for(i=0; i<length; i++)
    {
        intscore[i] =StringToInteger(scores[i]);
    }
    //sort(array, array+n, std::greater<int>());
    sort(intscore,intscore+length,greater<int>()); //Use the start and end like this
    for(i=0; i<length; i++)
    {
        scores[i]=ToString(intscore[i]);
    }

    //write sorted scores to file
    fstream fscorefile;
    fscorefile.open("score.txt",ios::out);
    if(!fscorefile)
    {
        cout<<"error3"<<endl;
    }
    for(int j=0; j<length; j++)
    {
        fscorefile<<scores[j]<<endl;
        //cout<<scores[j]<<endl;
    }
    fscorefile.close();
    //print updated scores
}

