//////////////////////////////MAIN MENU/////////////////////////////////////
#ifndef MENU
#define MENU

#include "header.hpp"
#include <conio.h>
#include <cstring>
#include <vector>
#include <windows.h>
#include "game.hpp"
#include "load.hpp"

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

using namespace std;

class Menu
{
public:
    Menu();
    void run();
private:
    void processEvents();
    void updateOptionText();
    void render();
    void load();
    void exitMenu();
    void instructions();
    void highscores();

private:
    string Option[4] = { "PLAY","SCORES","INSTRUCTIONS","EXIT"};
    sf::RenderWindow mWindow;
    sf::Texture mTexture;
    sf::Sprite  mSprite;
    sf::Font mFont;
    sf::Text mText;//loadText,loading;
    sf::Font oFont;
    vector<sf::Text> mOption;
    int mOptionIndex;
    Game game;
    Load l;

    string instruction;
    sf::Text mInstruction;
    sf::Sprite background;
    // object declaration of Game class
};


Menu ::Menu() : mWindow(sf::VideoMode(900,642), "Hot-Pursuit"),
    mTexture(),mSprite(),mOptionIndex(0),instruction(),mInstruction(),background()
{
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(sf::Vector2i(177,0));
    if(!mTexture.loadFromFile("resource/image/menu.png"))
    {
        cout<<"No File!!"<<endl;
    }
    mSprite.setTexture(mTexture);
    mSprite.setPosition(0,0);
    ////////////////////////Font Load////////////////////////////////////
    if(!mFont.loadFromFile("resource/fonts/PatrioticNepal_rabinsxp.ttf"))
        cout<<"Error Loading menu font"<<endl;
    mText.setFont(mFont);
    mText.setString("HOT PURSUIT");
    mText.setCharacterSize(117);
    mText.setColor(sf::Color(255,255,255,197));

    if(!oFont.loadFromFile("resource/fonts/leafy.otf"))
        cout<<"Error Loading menu font"<<endl;


    instruction = "\t\t Instructions \n\n Keys \n A - Drift Right \n D - Drift Left \n Drift you way through obstacles. \n Outrun the Cops and loose the chase. \n Do not let the cops get you . ";
    mInstruction.setFont(oFont);
    mInstruction.setString(instruction);
    mInstruction.setCharacterSize(50);
    background.setTexture(mTexture);
    background.setColor(sf::Color(255,255,255,150));

    for(int i = 0; i<4 ; i++)
    {
        sf::Text tempOption;
        tempOption.setFont(oFont);
        tempOption.setString(Option[i]);
        tempOption.setCharacterSize(40);
        tempOption.setPosition(sf::Vector2f(650,447+(i*47)));
        mOption.push_back(tempOption);
    }
    updateOptionText();
}

void Menu::run()
{
    while (mWindow.isOpen())
    {
        processEvents();
        render();
    }
}

void Menu::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            exitMenu();
        if (event.type==sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                if (mOptionIndex > 0)
                    mOptionIndex--;
                else
                    mOptionIndex = mOption.size() - 1;
                updateOptionText();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                if (mOptionIndex < mOption.size() - 1)
                    mOptionIndex++;
                else
                    mOptionIndex = 0;
                updateOptionText();
            }

            if (event.key.code == sf::Keyboard::Return)
            {
                switch(mOptionIndex)
                {
                case 0 :
                    mWindow.close();
                    l.run();
                    //Menu window is close after user selects play option
                    game.run(); //game window opens
                    break;
                case 1 :
                    highscores();
                    break;
                case 2 :
                    instructions();
                    break;
                case 3 :
                    exitMenu();
                }
            }
        }
    }
}

void Menu::updateOptionText()
{

    if (mOption.empty())
        return;
    for(int i = 0 ; i < 4 ; i++)
    {
        mOption[i].setColor(sf::Color::White);
        mOption[i].setCharacterSize(40);
    }
    mOption[mOptionIndex].setColor(sf::Color::Red);
    mOption[mOptionIndex].setStyle(sf::Text::Bold | sf::Text::Underlined);
    mOption[mOptionIndex].setCharacterSize(50);
}

void Menu::render()
{
    mWindow.clear();
    mWindow.draw(mSprite);
    mWindow.draw(mText);
    for(int i = 0; i<mOption.size(); i++)
        mWindow.draw(mOption[i]);
    mWindow.display();
}

void Menu :: exitMenu(void)
{
    int msgboxID = MessageBox(NULL, "Are you sure you want to Exit?", "EXIT", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2);
    switch (msgboxID)
    {
    case IDYES:
        mWindow.close();
        exit(1);
    case IDNO:
        break;
    }
}

void Menu::instructions()
{
    mWindow.clear();
    mWindow.draw(background);
    mWindow.draw(mInstruction);
    mWindow.display();
    Sleep(4000);
    Menu();
}

void Menu::highscores()
{
    fstream scorefile;
    scorefile.open("score.txt",ios::in);
    if(!scorefile)
        cout<<"error4"<<endl;
    //scorefile.seekp(0);
    static int i=0;
    string position[5];
    string scores[5];
    for(i=0; i<5; i++)
    {
        scorefile>>scores[i];
        position[i]=toString(i+1);
    }
    scorefile.close();


    mWindow.clear();
    mWindow.draw(background);

    string temp_display;
    sf::Text score_display;
    score_display.setFont(oFont);
    score_display.setCharacterSize(40);

    sf::Text disp_highscore;
    disp_highscore.setFont(oFont);
    disp_highscore.setCharacterSize(77);
    disp_highscore.setString("HIGHSCORE");
    disp_highscore.setPosition(sf::Vector2f(mWindow.getSize().x/3,50));
    mWindow.draw(disp_highscore);

    for(i=0; i<5; i++)
    {
        temp_display = position[i]+".    "+scores[i];
        score_display.setString(temp_display);
        score_display.setPosition(sf::Vector2f(100,200+(i*50)));
        mWindow.draw(score_display);
        cout<<temp_display;
    }
    mWindow.display();
    Sleep(5000);
}
#endif // MENU



