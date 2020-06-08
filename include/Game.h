#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"


class Game
{
    public:
        Game();
        virtual ~Game();
        void update();
        int render();
        bool getGameIsRunning();
        sf::RenderWindow* getWindow();
        void renderScore();
        void initializeVariables();
        void initializeImmutableCanvas();
        void initializeScore();
        void tick();
        void renderNewObject();
        void iterateOverNewObject();
        void handleEvent();
        int score;

    protected:

    private:
        sf::RenderWindow* window;
        bool gameIsRunning;
        sf::RectangleShape* centeredRectangleShape;
        sf::Text scoreText;
        std::time_t currentTick;
        std::time_t deltaTime;
        bool newObjectIsRender;
        float newObjectBasePosX;
        float beforeObjectBasePosX;
        float newObjectBasePosY;
        void generateGravity();
        int randomNumber;
        sf::Event event;
        void handleKeyPress(sf::Event event);
        void move(int direction);
        void checkHorizontalColision();
        void checkVerticalColision();
        bool colided;
        void resetMutableVariablesOnColision();
        void drawColidedRect();
        bool checkInterObjectColisionsVertical();
        bool checkInterObjectColisionsHorizontal(int direction);
        void addGravity();
        void gameOver();
        void checkTetris();
        void tetris(int column);
        void copyAllMapArrayToNextLine();
        int limitOfCopy;
        int countOfCopy;
        void rotateObject();
};

#endif // GAME_H
