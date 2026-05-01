#include "scene_menu.hpp"
#include "../components.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../util.h"
#include "../game_data.hpp"
#include <iostream>

Scene_Menu::Scene_Menu(GameData* gameData) : Scene(gameData) {
    sf::Texture* tulipTexture = m_gameData->tulipTexture;
    sf::Font* font = m_gameData->font;

    Entity* m_background = m_entityManager.create("Background");
    m_background->colorComponent = new Component_Color(sf::Color(255, 255, 255));
    m_background->transformComponent = new Component_Transform(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 1.0f), 0.0f);
    m_background->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(640.0f, 480.0f));

    m_title = m_entityManager.create("Text");
    m_textBounds = getTextSize("PLANTS VS ROBOTS", font, 48);
    m_title->colorComponent = new Component_Color(sf::Color::Black);
    m_title->textComponent = new Component_Text(font, "PLANTS VS ROBOTS", 48);
    m_title->transformComponent = new Component_Transform(
        sf::Vector2f(320.f,
                     70.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);

    Entity* tulip = m_entityManager.create("Dynamic");
    tulip->colorComponent = new Component_Color(sf::Color::White);
    tulip->transformComponent = new Component_Transform(sf::Vector2f(m_title->transformComponent->position.x-m_textBounds.size.x/2-32.0f-5.0f, m_title->transformComponent->position.y-m_textBounds.size.y/2-32.0f-5.0f), sf::Vector2f(2.0f, 2.0f), 0.0f);
    tulip->spriteComponent = new Component_Sprite(tulipTexture);

    sf::FloatRect playBounds = getTextSize("Levels", font, 40);
    sf::FloatRect shopBounds = getTextSize("Shop", font, 40);
    sf::FloatRect quitBounds = getTextSize("Quit", font, 40);

    m_playButton = m_entityManager.create("Button");
    m_playButton->colorComponent = new Component_Color(sf::Color::Green);
    m_playButton->transformComponent = new Component_Transform(
        sf::Vector2f(320.f,
                     150.f),
        sf::Vector2f(1.1f, 1.3f), 0.0f, Origin::Center);
    m_playButton->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(playBounds.size.x, playBounds.size.y));

    Entity* playLabel = m_entityManager.create("Label");
    playLabel->colorComponent = new Component_Color(sf::Color::Black);
    playLabel->textComponent = new Component_Text(font, "Levels", 40);
    playLabel->transformComponent = new Component_Transform(
        sf::Vector2f(320.f, 150.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);

    m_shopButton = m_entityManager.create("Button");
    m_shopButton->colorComponent = new Component_Color(sf::Color::Green);
    m_shopButton->transformComponent = new Component_Transform(
        sf::Vector2f(320.f,
                     200.f),
        sf::Vector2f(1.1f, 1.3f), 0.0f, Origin::Center);
    m_shopButton->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(shopBounds.size.x, shopBounds.size.y));

    Entity* shopLabel = m_entityManager.create("Label");
    shopLabel->colorComponent = new Component_Color(sf::Color::Black);
    shopLabel->textComponent = new Component_Text(font, "Shop", 40);
    shopLabel->transformComponent = new Component_Transform(
        sf::Vector2f(320.f, 200.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);

    m_quitButton = m_entityManager.create("Button");
    m_quitButton->colorComponent = new Component_Color(sf::Color::Green);
    m_quitButton->transformComponent = new Component_Transform(
        sf::Vector2f(320.f,
                     250.f),
        sf::Vector2f(1.1f, 1.3f), 0.0f, Origin::Center);
    m_quitButton->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(quitBounds.size.x, quitBounds.size.y));

    Entity* quitLabel = m_entityManager.create("Label");
    quitLabel->colorComponent = new Component_Color(sf::Color::Black);
    quitLabel->textComponent = new Component_Text(font, "Quit", 40);
    quitLabel->transformComponent = new Component_Transform(
        sf::Vector2f(320.f, 250.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);   
}

void Scene_Menu::update() {
    Scene::update();
    for (Entity* e : m_entityManager.getEntities("Dynamic")) {
        if (m_tulipDirection == 0) {
            e->transformComponent->position.x += 1.0f;
            if (e->transformComponent->position.x >= m_title->transformComponent->position.x+m_textBounds.size.x/2+5.0f) {
                m_tulipDirection = 1;
            }
        } else if (m_tulipDirection == 1) {
            e->transformComponent->position.y += 1.0f;
            if (e->transformComponent->position.y >= m_title->transformComponent->position.y+m_textBounds.size.y/2+5.0f) {
                m_tulipDirection = 2;
            }
        } else if (m_tulipDirection == 2) {
            e->transformComponent->position.x -= 1.0f;
            if (e->transformComponent->position.x <= m_title->transformComponent->position.x-m_textBounds.size.x/2-32.0f-5.0f) {
                m_tulipDirection = 3;
            }
        } else if (m_tulipDirection == 3) {
            e->transformComponent->position.y -=1.0f;
            if (e->transformComponent->position.y <= m_title->transformComponent->position.y-m_textBounds.size.y/2-32.0f-5.0f) {
                m_tulipDirection = 0;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && (!m_downPressed || m_currentFrame > m_nextInputTime)) {
        m_currentSelection = (m_currentSelection + 1) % 3;
        m_downPressed = true;
        m_nextInputTime = m_currentFrame + 20;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        m_downPressed = false;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && (!m_upPressed || m_currentFrame > m_nextInputTime)) {
        m_currentSelection = (m_currentSelection - 1 + 3) % 3;
        m_upPressed = true;
        m_nextInputTime = m_currentFrame + 20;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        m_upPressed = false;
    }

    m_playButton->setHidden(m_currentSelection != 0);
    m_shopButton->setHidden(m_currentSelection != 1);
    m_quitButton->setHidden(m_currentSelection != 2);

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Enter)]) {
        if (m_currentSelection == 0) {
            switchScene("levels");
        } else if (m_currentSelection == 1) {
            switchScene("shop");
        } else if (m_currentSelection == 2) {
            exit(0);
        }
    }
}