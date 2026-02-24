#include "../include/Game.hpp"

Game::Game() 
    : window(sf::VideoMode({800, 600}), "Gioco") {
    window.setFramerateLimit(144);

    // Inizializziamo la vista con la dimensione originale
    view.setSize({800.f, 600.f});
    view.setCenter({400.f, 300.f});

    player.setSize({50.f, 50.f});
    player.setFillColor(sf::Color::Green);
    player.setPosition({100.f, 100.f});

    wall.setSize({100.f, 100.f});
    wall.setFillColor(sf::Color::Red);
    wall.setPosition({400.f, 300.f});
}

void Game::run() {
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        // Evita distorsioni al ridimensionamento
        else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            // Aggiorniamo la viewport per mantenere il rapporto d'aspetto
            sf::FloatRect visibleArea({0.f, 0.f}, {(float)resized->size.x, (float)resized->size.y});
            window.setView(sf::View(visibleArea)); 
            // Nota: se vuoi che il mondo resti della stessa dimensione "zoomata", 
            // usa view e calcola la viewport proporzionale.
        }
    }

    movement = {0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;
}

void Game::update(sf::Time deltaTime) {
    sf::Vector2f frameMovement = movement * speed * deltaTime.asSeconds();
    
    player.move(frameMovement);
    
    handleCollision(frameMovement);
    handleWindowCollision(); // Controlla i bordi dopo il movimento
}

void Game::handleWindowCollision() {
    sf::Vector2f pos = player.getPosition();
    sf::Vector2f size = player.getSize();
    // Otteniamo la dimensione attuale della finestra/vista
    sf::Vector2f winSize = window.getView().getSize();

    // Bordi orizzontali
    if (pos.x < 0) pos.x = 0;
    if (pos.x + size.x > winSize.x) pos.x = winSize.x - size.x;

    // Bordi verticali
    if (pos.y < 0) pos.y = 0;
    if (pos.y + size.y > winSize.y) pos.y = winSize.y - size.y;

    player.setPosition(pos);
}

void Game::handleCollision(sf::Vector2f lastMovement) {
    if (auto intersection = player.getGlobalBounds().findIntersection(wall.getGlobalBounds())) {
        player.move(-lastMovement);
    }
}

void Game::render() {
    window.clear();
    window.draw(wall);
    window.draw(player);
    window.display();
}
