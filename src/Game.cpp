#include "../include/Game.hpp"

Game::Game() 
    : m_window(sf::VideoMode({800, 600}), "SFML 3.0 Game") {
    
    m_player.setSize({50.f, 50.f});
    m_player.setFillColor(sf::Color::Green);
    m_player.setPosition({400.f, 300.f});
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        // Calcolo Delta Time
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}

void Game::update(float dt) {
    sf::Vector2f movement{0.f, 0.f};

    // Sintassi SFML 3.0: sf::Keyboard::Key::...
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

    // Applichiamo il movimento corretto con dt
    m_player.move(movement * m_speed * dt);
}

void Game::render() {
    m_window.clear(sf::Color::Black); // Se vedi nero, il ciclo funziona
    m_window.draw(m_player);          // Disegna il quadrato verde
    m_window.display();
}
