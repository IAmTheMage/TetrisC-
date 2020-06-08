#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>


class Object
{
    public:
        Object(float canvasWidth, float canvasHeight, int xCoeficient, int yCoeficient, int basePositionX, int basePositionY);
        sf::RectangleShape getObject();
        float getPosX();
        float getPosY();
        virtual ~Object();

    protected:

    private:
        sf::RectangleShape rect;
        float objectWidth;
        float objectHeight;
        float objectPosX;
        float objectPosY;
};

#endif // OBJECT_H
