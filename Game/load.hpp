#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <cstring>
#include <iostream>
#include <vector>
#include <windows.h>

class Load
{
public:
    Load();

    void run();
private:
    sf::RenderWindow lWindow;
    sf::Font lFont;
    sf::Text lText;
    sf::Text load;
};

Load ::Load() : lWindow(sf::VideoMode(900,642), "Hot Persuit"),lFont(),lText()
{
    lWindow.setPosition(sf::Vector2i(177,0));
    lWindow.setFramerateLimit(60);
    if(!lFont.loadFromFile("resource/fonts/PatrioticNepal_rabinsxp.ttf"))
        cout<<"Error Loading menu font"<<endl;
    lText.setFont(lFont);
    lText.setString("HOT PURSUIT");
    lText.setCharacterSize(117);
    lText.setColor(sf::Color(0,0,0));
    lText.setPosition(17,177);
    load.setFont(lFont);
    load.setString("III");
    load.setCharacterSize(57);
}

void Load::run()
{
    lWindow.clear();
    sf::Event event;
    for (int i = 0; i < 77 ; i++)
    {
        while (lWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                lWindow.close();
            break;
        }
        lText.setColor(sf::Color(255,255,255,i*3));
        load.setPosition(i*27,477);
        Sleep(50);
        lWindow.draw(load);
        lWindow.draw(lText);
        lWindow.display();
        load.setColor(sf::Color(rand()%255,rand()%255,rand()%255));
    }
    lWindow.close();
}




