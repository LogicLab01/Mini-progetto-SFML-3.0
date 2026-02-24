#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void handleCollision(sf::Vector2f lMove);
    void handleWindowCollision(); // Nuova collisione bordi

    sf::RenderWindow window;
    sf::View view; // Per mantenere le proporzioni
    sf::RectangleShape player;
    sf::RectangleShape wall;
    sf::Vector2f movement;
    sf::Clock clock;
    
    const float speed = 400.f;
};