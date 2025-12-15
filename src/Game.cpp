/* ===  INCLUDES  === */

// --- Class Header ---
#include "Game.hpp"

// --- Standard C++ Libraries ---
#include <iostream>
#include <cmath>


/* ===  LIFECYCLE & EXECUTION  === */

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Breakout - Demo Version"),
      m_state(GameState::Running),
      m_paddle(400, 550),
      m_ball(400, 300)
{
    // 0. Window Setup
    m_window.setFramerateLimit(60);

    // 1. Load Resources
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "ERROR: Could not load arial.ttf" << std::endl;
    }

    // 2. Setup User Interface
    m_text.setFont(m_font);
    m_text.setCharacterSize(50);
    m_text.setFillColor(sf::Color::White);
    m_text.setStyle(sf::Text::Bold);

    // 3. Bind Inputs
    // We bind keys using lambdas to call member methods
    m_inputManager.bindKey(sf::Keyboard::Left,  [this](){ m_paddle.move(-m_paddle.speed * 0.016f, 0.f); });
    m_inputManager.bindKey(sf::Keyboard::Right, [this](){ m_paddle.move(m_paddle.speed * 0.016f, 0.f); });

    // Game Flow Control (Restart)
    m_inputManager.bindKey(sf::Keyboard::Space, [this](){
        if (m_state != GameState::Running) {
            resetLevel();
        }
    });

    // 4. Initialize Game State
    resetLevel();
}

void Game::run() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}


/* ===  CORE LOGIC  === */

void Game::processEvents() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Game::update(float deltaTime) {
    m_inputManager.update(); // Poll inputs every frame

    if (m_state == GameState::Running) {
        m_paddle.update(deltaTime);
        m_ball.update(deltaTime);

        // --- Physics & Collisions ---

        // 1. Paddle vs Ball
        if (m_paddle.checkCollision(m_ball)) {
            m_ball.velocity.y = -std::abs(m_ball.velocity.y); // Bounce UP
            m_ball.move(0.f, -10.f); // Unstick
        }

        // 2. Bricks vs Ball
        for (auto& brick : m_bricks) {
            if (!brick.isDestroyed && brick.checkCollision(m_ball)) {
                brick.isDestroyed = true;
                m_ball.velocity.y = -m_ball.velocity.y;
                break;
            }
        }

        // --- Game Rules ---

        // Check Victory
        int remainingBricks = 0;
        for (const auto& brick : m_bricks) {
            if (!brick.isDestroyed) remainingBricks++;
        }

        if (remainingBricks == 0) {
            m_state = GameState::Victory;
            centerText("VICTORY! Press Space");
        }

        // Check Defeat
        if (m_ball.getPosition().y > 600.f) {
            m_state = GameState::GameOver;
            centerText("GAME OVER\nPress Space");
            m_text.setFillColor(sf::Color::Red);
        }
    }
}

void Game::render() {
    m_window.clear(sf::Color::Black);

    if (m_state == GameState::Running) {
        // Draw World
        for (const auto& brick : m_bricks) {
            brick.draw(m_window, sf::RenderStates::Default);
        }
        m_window.draw(m_paddle);
        m_window.draw(m_ball);
    }
    else {
        // Draw UI
        m_window.draw(m_text);
    }

    m_window.display();
}


/* ===  HELPER METHODS  === */

void Game::resetLevel() {
    m_state = GameState::Running;

    // Reset Entity Positions
    m_paddle.setPosition(400, 550);
    m_ball.setPosition(400, 300);
    m_ball.velocity = {250.f, -250.f};

    // Re-generate Bricks Grid
    m_bricks.clear();
    constexpr int rows = 5;

    for (int i = 0; i < rows; ++i) {
        constexpr int cols = 10;
        for (int j = 0; j < cols; ++j) {
            constexpr float startX = 130.f;
            constexpr float startY = 60.f;
            float x = startX + static_cast<float>(j) * 65.f;
            float y = startY + static_cast<float>(i) * 25.f;
            m_bricks.emplace_back(x, y);
        }
    }
}

void Game::centerText(const std::string& str) {
    m_text.setString(str);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    m_text.setPosition(400.f, 300.f);
}
