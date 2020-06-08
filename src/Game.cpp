#include "Game.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstring>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <ctime>
#include <random>
#include <experimental/random>
#include <cstdlib>
#include <conio.h>

#define WIDTH 800
#define HEIGHT 600
#define SCALE 1
#define TITLE "Tetris for JONAS"
#define FPS 30
#define CANVASWIDTH WIDTH / 2
#define CANVASPOSX 200.0f
#define CANVASOUTLINESIZE 3

const int allMapRowLimit = CANVASWIDTH / (CANVASWIDTH / 10);

const int allMapColumnLimit = HEIGHT / (HEIGHT / 20);

int allMapArray[allMapColumnLimit][allMapRowLimit];

bool gravityIsGenerated = false;

bool gameOverIsChecked = false;

struct ObjectPoint {
    int column;
    int row;
};



ObjectPoint objectPossiblePositionsMaped[28][4] = {
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            0,2
        },
        {
            0,3
        },
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            0,2
        },
        {
            1,2
        }
    },
    {
        {
            1,0
        },
        {
            1,1
        },
        {
            1,2
        },
        {
            0,2
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            1,0
        },
        {
            1,1
        }
    },
    {
        {
            0,1
        },
        {
            1,0
        },
        {
            1,1
        },
        {
            2,0
        }
    },
    {
        {
            0,0
        },
        {
            1,0
        },
        {
            1,1
        },
        {
            2,1
        }
    },
    {
        {
            1,0
        },
        {
            0,1
        },
        {
            1,1
        },
        {
            2,1
        }
    },
    {
        {
            0,0
        },
        {
            1,0
        },
        {
            2,0
        },
        {
            3,0
        },
    },
    {
        {
            0,1
        },
        {
            1,1
        },
        {
            2,1
        },
        {
            2,0
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            1,1
        },
        {
            2,1
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            1,0
        },
        {
            1,1
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            1,1
        },
        {
            1,2
        }
    },
    {
        {
            0,1
        },
        {
            0,2
        },
        {
            1,0
        },
        {
            1,1
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            0,2
        },
        {
            1,1
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            0,2
        },
        {
            0,3
        },
    },
    {
        {
            0,0
        },
        {
            1,0
        },
        {
            1,1
        },
        {
            1,2
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            0,2
        },
        {
            1,0
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            1,0
        },
        {
            1,1
        }
    },
    {
        {
            0,1
        },
        {
            1,0
        },
        {
            1,1
        },
        {
            2,0
        }
    },
    {
        {
            0,0
        },
        {
            1,0
        },
        {
            1,1
        },
        {
            2,1
        }
    },
    {
        {
            0,0
        },
        {
            1,0
        },
        {
            2,0
        },
        {
            1,1
        }
    },
    {
        {
            0,0
        },
        {
            1,0
        },
        {
            2,0
        },
        {
            3,0
        },
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            1,0
        },
        {
            2,0
        }
    },
    {
        {
            0,0
        },
        {
            1,0
        },
        {
            2,0
        },
        {
            2,1
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            1,0
        },
        {
            1,1
        }
    },
    {
        {
            0,0
        },
        {
            0,1
        },
        {
            1,1
        },
        {
            1,2
        }
    },
    {
        {
            0,1
        },
        {
            0,2
        },
        {
            1,0
        },
        {
            1,1
        }
    },
    {
        {
            0,1
        },
        {
            1,0
        },
        {
            1,1
        },
        {
            1,2
        }
    },
};

int newObjectPossiblePositions[4][4] = {0};

void Game::initializeVariables() {
    //PlaySound("Tetris_theme.wav",NULL,SND_ASYNC);
    this->window = new sf::RenderWindow(sf::VideoMode(WIDTH * SCALE, HEIGHT * SCALE), TITLE);
    this->gameIsRunning = true;
    this->score = 0;
    this->currentTick = 0;
    this->newObjectIsRender = false;
    for(int i = 0; i < allMapColumnLimit; i++) {
        for(int j = 0; j < allMapRowLimit; j++) {
            allMapArray[i][j] = 0;
        }
    }
    for(int i = 0; i <= 3;i++) {
        for(int j = 0; j <= 3; j++) {
            newObjectPossiblePositions[i][j] = 0;
        }
    }
    this->newObjectBasePosX = 0;
    this->newObjectBasePosY = 0;
    srand(time(0));

    this->randomNumber = rand() % 7;
    this->colided = false;
}

void Game::initializeImmutableCanvas() {
    sf::RectangleShape centeredRectangleShape(sf::Vector2f(CANVASWIDTH, HEIGHT * SCALE));
    centeredRectangleShape.setOutlineThickness(CANVASOUTLINESIZE);
    centeredRectangleShape.setOutlineColor(sf::Color::White);
    centeredRectangleShape.setFillColor(sf::Color::Black);
    centeredRectangleShape.setPosition(sf::Vector2f(CANVASPOSX, 0.0f));
    this->window->draw(centeredRectangleShape);
}

void Game::initializeScore() {
    char scoreStatus[40] = "Score: ";
    std::string scoreString = std::to_string(this->score);
    char const *scoreChar = scoreString.c_str();
    strcat(scoreStatus, scoreChar);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    this->scoreText = sf::Text();
    this->scoreText.setFont(font);
    this->scoreText.setPosition(sf::Vector2f(20.0f, 0.0f));
    this->scoreText.setString(scoreStatus);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setCharacterSize(20);
    this->window->draw(this->scoreText);
}

void Game::update()
{
    if(this->getGameIsRunning()) {
        if(gameOverIsChecked == false) {
            if(this->checkInterObjectColisionsVertical() == true) {
                this->gameOver();
            }
            gameOverIsChecked = true;
        }
        char key;
        this->deltaTime = std::time(nullptr) - this->currentTick;
        if(this->deltaTime >= 1 / 30) {
            this->currentTick = std::time(nullptr);
            this->tick();

        }
        if(this->deltaTime >= 1) {
            if(gravityIsGenerated == false) {
                gravityIsGenerated = true;
            }
            else {
                this->generateGravity();
            }
        }
    }

}

void Game::generateGravity() {
    this->newObjectBasePosY += HEIGHT / 20;
}

void Game::tick()
{
    this->window -> clear();
    this->initializeImmutableCanvas();
    this->initializeScore();
    this->renderNewObject();
    this->drawColidedRect();
    this->checkTetris();
    this->window->display();
}


int Game::render()
{
    this->initializeImmutableCanvas();
    this->initializeScore();
    this->window->display();
    return 0;
}

bool Game::getGameIsRunning()
{
    return this->gameIsRunning;
}

sf::RenderWindow* Game::getWindow() {
    return this->window;
}

void Game::renderNewObject() {
    ObjectPoint points[1][4] = {0};
    this->checkHorizontalColision();
    this->checkVerticalColision();
    this->checkInterObjectColisionsVertical();
    for(int i = 0; i < 4; i++) {
        points[0][i] = objectPossiblePositionsMaped[this->randomNumber][i];
        Object object = Object(CANVASWIDTH, HEIGHT, points[0][i].column, points[0][i].row, this->newObjectBasePosX, this->newObjectBasePosY);
        sf::RectangleShape rect = object.getObject();
        this->window->draw(rect);
    }
}

void Game::checkHorizontalColision() {
    int maxColumn = 0;
    int minColumn = 3;
    for(int iterat = 0; iterat < 4; iterat++) {
        if(maxColumn <= objectPossiblePositionsMaped[this->randomNumber][iterat].column) {
            maxColumn = objectPossiblePositionsMaped[this->randomNumber][iterat].column;
        }
        if(minColumn >= objectPossiblePositionsMaped[this->randomNumber][iterat].column) {
            minColumn = objectPossiblePositionsMaped[this->randomNumber][iterat].column;
        }

    }
    if(this->newObjectBasePosX > CANVASWIDTH - (CANVASWIDTH / 10 * (maxColumn + 1))) {
        this->newObjectBasePosX = CANVASWIDTH - (CANVASWIDTH / 10 * (maxColumn + 1));
    }
    if(this->newObjectBasePosX <= 0) {
        this->newObjectBasePosX = 0;
    }
}

void Game::checkVerticalColision() {
    int maxLine = 0;
    bool colisionChecked = false;
    for(int iterat = 0; iterat < 4; iterat++) {
        if(maxLine <= objectPossiblePositionsMaped[this->randomNumber][iterat].row) {
            maxLine = objectPossiblePositionsMaped[this->randomNumber][iterat].row;
        }
    }
    if(this->newObjectBasePosY > HEIGHT - (HEIGHT / 20 * (maxLine + 1))) {
        this->newObjectBasePosY = HEIGHT - (HEIGHT / 20 * (maxLine + 1));
        colisionChecked = true;
    }

    if(colisionChecked == true && this->colided == false) {
        int firstBrickPositionY = this->newObjectBasePosY / (HEIGHT / 20);
        int firstBrickPositionX = this->newObjectBasePosX / (CANVASWIDTH / 10);
        for(int i = 0; i < 4; i++) {
            allMapArray[firstBrickPositionY + objectPossiblePositionsMaped[this->randomNumber][i].row][firstBrickPositionX + objectPossiblePositionsMaped[this->randomNumber][i].column] = 1;
        }
        this->colided = true;
        this->resetMutableVariablesOnColision();
    }
}

bool Game::checkInterObjectColisionsVertical() {
    bool isColided = false;
    for(int i = 0; i < 4; i++) {
        int mappedObjectCoeficientX = objectPossiblePositionsMaped[this->randomNumber][i].column;
        int mappedObjectCoeficientY = objectPossiblePositionsMaped[this->randomNumber][i].row;
        int finalMappedObjectPositionX = this->newObjectBasePosX / (CANVASWIDTH / 10) + mappedObjectCoeficientX;
        int finalMappedObjectPositionY = this->newObjectBasePosY / (HEIGHT / 20) + mappedObjectCoeficientY;
        if(allMapArray[finalMappedObjectPositionY][finalMappedObjectPositionX] == 1) {
            isColided = true;
            break;
        }
    }
    if(isColided == true) {
        int firstBrickPositionY = this->newObjectBasePosY / (HEIGHT / 20) - 1;
        int firstBrickPositionX = this->newObjectBasePosX / (CANVASWIDTH / 10);
        for(int i = 0; i < 4; i++) {
            allMapArray[firstBrickPositionY + objectPossiblePositionsMaped[this->randomNumber][i].row][firstBrickPositionX + objectPossiblePositionsMaped[this->randomNumber][i].column] = 1;
        }
        this->resetMutableVariablesOnColision();
    }
    return isColided;
}

bool Game::checkInterObjectColisionsHorizontal(int direction) {
    bool isColided = true;
    for(int i = 0; i < 4; i++) {
        int mappedObjectCoeficientX = objectPossiblePositionsMaped[this->randomNumber][i].column;
        int mappedObjectCoeficientY = objectPossiblePositionsMaped[this->randomNumber][i].row;
        int finalMappedObjectPositionX = this->newObjectBasePosX / (CANVASWIDTH / 10) + mappedObjectCoeficientX;
        int finalMappedObjectPositionY = this->newObjectBasePosY / (HEIGHT / 20) + mappedObjectCoeficientY;
        if(allMapArray[finalMappedObjectPositionY][finalMappedObjectPositionX + direction] == 1) {
            isColided = false;
            break;
        }
    }
    return isColided;
}

void Game::resetMutableVariablesOnColision() {
    this->newObjectBasePosX = 0;
    this->newObjectBasePosY = 0;
    srand(time(0));
    this->randomNumber = rand() % 6;
    this->colided = false;
    gravityIsGenerated = false;
    gameOverIsChecked = false;
}

void Game::drawColidedRect() {
    for(int i = 0; i < allMapColumnLimit; i++) {
        for(int j = 0; j < allMapRowLimit; j++) {
            int stateOfMappedItem = allMapArray[i][j];
            if(stateOfMappedItem == 1) {
                Object object = Object(CANVASWIDTH, HEIGHT,j, i, 0, 0);
                sf::RectangleShape rect = object.getObject();
                this->window->draw(rect);
            }
        }
    }
}

void Game::handleEvent() {
    while(this->window->pollEvent(this->event)) {
        if(this->event.type == sf::Event::Closed) {
            window -> close();
        }
        if(event.type == sf::Event::KeyPressed) {
            this->handleKeyPress(event);
        }
    }
}

void Game::handleKeyPress(sf::Event event) {
    this->beforeObjectBasePosX = this->newObjectBasePosX;
    if(event.key.code == sf::Keyboard::Left) {
        this->move(-1);
    }
    if(event.key.code == sf::Keyboard::Right) {
        this->move(1);
    }
    if(event.key.code == sf::Keyboard::Down) {
        this->generateGravity();
    }
    if(event.key.code == sf::Keyboard::Up) {
        this->rotateObject();
    }
}

void Game::checkTetris() {
    int counterOfTetris = 0;
    for(int i = 0; i < allMapColumnLimit; i++) {
        int count = 0;
        for(int j = 0; j < allMapRowLimit; j++) {
            if(allMapArray[i][j] == 1) {
                count++;
            }
        }
        if(count == 10) {
            this->tetris(i);
        }
    }
    //this->copyAllMapArrayToNextLine();
}

void Game::tetris(int column) {
    std::cout << column << "\n";
    for(int line = 0; line < allMapRowLimit; line++) {
        allMapArray[column][line] = 0;
    }
    this->score += 100;
    this->limitOfCopy = column;
    this->copyAllMapArrayToNextLine();
}

void Game::copyAllMapArrayToNextLine(){
    int placeholderValue = 0;
    /*for(int limit = 0; limit < this->limitOfCopy - 1; limit++) {
        for(int line = 0; line < allMapRowLimit; line++) {
            allMapArray[limit + 1][line] = allMapArray[limit][line];
        }
    }*/
    for(int limit = this->limitOfCopy; limit >= 0; limit-- ) {
        for(int row = 0; row < allMapRowLimit; row++) {
            if(limit > 0) {
                placeholderValue = allMapArray[limit - 1][row];
                allMapArray[limit][row] = placeholderValue;
            }
        }
    }
}

void Game::move(int direction) {
    if(this->checkInterObjectColisionsHorizontal(direction)) {
        this->newObjectBasePosX += direction * (CANVASWIDTH / 10);
    }
}

void Game::rotateObject() {
    if(this->randomNumber + 7 < 28) {
        this->randomNumber += 7;
    }
    else {
        this->randomNumber = (this->randomNumber + 7) - 28;
    }
}

void Game::gameOver() {
    this->gameIsRunning = false;
}

Game::Game()
{
    this->initializeVariables();
    this->render();
}

Game::~Game()
{

}

