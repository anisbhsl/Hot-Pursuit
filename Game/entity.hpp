#ifndef ENTITY
#define ENTITY

#include "header.hpp"

class Entity
{
public:
    sf::Sprite eSprite;
    sf::RectangleShape rect;
    float movementSpeed;
    bool active;
    bool deleteIt;
};

#endif // ENTITY
