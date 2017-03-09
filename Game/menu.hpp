//////////////////////////////MAIN MENU/////////////////////////////////////
#include "header.hpp"

#include <cstring>
#include <vector>
#include <windows.h>

#include "game.hpp"
#include "load.hpp"

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
    Load l; // object declaration of Game class
};

Menu ::Menu() : mWindow(sf::VideoMode(900,642), "Hot-Pursuit"),
    mTexture(),mSprite(),mOptionIndex(0)
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
//////////////////////////////////Loading Menu///////////////////////////////////
/*
    loadText.setFont(mFont);
    loadText.setString("HOT PURSUIT");
    loadText.setCharacterSize(117);
    loadText.setColor(sf::Color(0,0,0));
    loadText.setPosition(17,177);
    loading.setFont(mFont);
    loading.setString("III");
    loading.setCharacterSize(57);
*/
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
                    cout<<"score"<<endl;
                    break;
                case 2 :
                    cout<<"Instructions"<<endl;
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




