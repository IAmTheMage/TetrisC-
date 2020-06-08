#include <SFML/Graphics.hpp>
#include <iostream>
#include <Game.h>

int main()
{
    Game *game = new Game();
    while(game->getGameIsRunning()) {
        sf::Event event;
        sf::RenderWindow* window = game->getWindow();
        /*while(window -> pollEvent(event)) {


            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Right) {
                    std::cout << "Right" << "\n";
                }
            }

        }*/
        game->handleEvent();

        game->update();
    }

}
