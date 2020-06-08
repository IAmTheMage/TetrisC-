#include "Object.h"
#include <iostream>
#include <SFML/Graphics.hpp>

float Object::getPosY() {
    return this->objectPosY;
}

float Object::getPosX() {
    return this->objectPosX;
}

Object::Object(float canvasWidth, float canvasHeight, int xCoeficient, int yCoeficient, int basePositionX, int basePositionY)
{
    this->objectWidth = canvasWidth / 10;
    this->objectPosX = (this->objectWidth * xCoeficient) + basePositionX + 200;
    this->objectHeight = canvasHeight / 20;
    this->objectPosY = (this->objectHeight * yCoeficient) + basePositionY;
    this->rect = sf::RectangleShape(sf::Vector2f(this->objectWidth, this->objectHeight));
    this->rect.setFillColor(sf::Color::White);
    this->rect.setPosition(sf::Vector2f(this->objectPosX, this->objectPosY));
}


Object::~Object()
{
    //dtor
}

sf::RectangleShape Object::getObject() {
    return this->rect;
}
