#define Game.h
#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
private:
    sf::RenderWindow* window;
public:
    Game() {
        std::cout << "Hello";
    };
    int render() {
    };
};
/*this->window = sf::VideoMode(800, 600), "SFML window";

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;*/
