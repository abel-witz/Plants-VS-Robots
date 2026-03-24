#include "scene_menu.hpp"
#include "../components.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../util.h"
#include "../game_data.hpp"
#include <iostream>

Scene_Menu::Scene_Menu(GameData* gameData) : Scene(gameData) {
    sf::Texture* m_tulipTexture = m_gameData->tulipTexture;
    sf::Font* m_font = m_gameData->font;

    Entity* background = m_entityManager.create("Background");
    background->colorComponent = new Component_Color(sf::Color(255, 255, 255));
    background->transformComponent = new Component_Transform(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 1.0f), 0.0f);
    background->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(640.0f, 480.0f));

    title = m_entityManager.create("Text");
    textBounds = getTextSize("PLANTS VS ROBOTS", m_font, 48);
    title->colorComponent = new Component_Color(sf::Color::Black);
    title->textComponent = new Component_Text(m_font, "PLANTS VS ROBOTS", 48);
    title->transformComponent = new Component_Transform(
        sf::Vector2f(320.f,
                     70.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);

    Entity* tulip = m_entityManager.create("Dynamic");
    tulip->colorComponent = new Component_Color(sf::Color::White);
    tulip->transformComponent = new Component_Transform(sf::Vector2f(title->transformComponent->position.x-textBounds.size.x/2-32.0f-5.0f, title->transformComponent->position.y-textBounds.size.y/2-32.0f-5.0f), sf::Vector2f(2.0f, 2.0f), 0.0f);
    tulip->spriteComponent = new Component_Sprite(m_tulipTexture);

    sf::FloatRect playBounds = getTextSize("Levels", m_font, 40);
    sf::FloatRect shopBounds = getTextSize("Shop", m_font, 40);
    sf::FloatRect quitBounds = getTextSize("Quit", m_font, 40);

    playButton = m_entityManager.create("Button");
    playButton->colorComponent = new Component_Color(sf::Color::Green);
    playButton->transformComponent = new Component_Transform(
        sf::Vector2f(320.f,
                     150.f),
        sf::Vector2f(1.1f, 1.3f), 0.0f, Origin::Center);
    playButton->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(playBounds.size.x, playBounds.size.y));

    Entity* playLabel = m_entityManager.create("Label");
    playLabel->colorComponent = new Component_Color(sf::Color::Black);
    playLabel->textComponent = new Component_Text(m_font, "Levels", 40);
    playLabel->transformComponent = new Component_Transform(
        sf::Vector2f(320.f, 150.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);

    shopButton = m_entityManager.create("Button");
    shopButton->colorComponent = new Component_Color(sf::Color::Green);
    shopButton->transformComponent = new Component_Transform(
        sf::Vector2f(320.f,
                     200.f),
        sf::Vector2f(1.1f, 1.3f), 0.0f, Origin::Center);
    shopButton->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(shopBounds.size.x, shopBounds.size.y));

    Entity* shopLabel = m_entityManager.create("Label");
    shopLabel->colorComponent = new Component_Color(sf::Color::Black);
    shopLabel->textComponent = new Component_Text(m_font, "Shop", 40);
    shopLabel->transformComponent = new Component_Transform(
        sf::Vector2f(320.f, 200.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);

    quitButton = m_entityManager.create("Button");
    quitButton->colorComponent = new Component_Color(sf::Color::Green);
    quitButton->transformComponent = new Component_Transform(
        sf::Vector2f(320.f,
                     250.f),
        sf::Vector2f(1.1f, 1.3f), 0.0f, Origin::Center);
    quitButton->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(quitBounds.size.x, quitBounds.size.y));

    Entity* quitLabel = m_entityManager.create("Label");
    quitLabel->colorComponent = new Component_Color(sf::Color::Black);
    quitLabel->textComponent = new Component_Text(m_font, "Quit", 40);
    quitLabel->transformComponent = new Component_Transform(
        sf::Vector2f(320.f, 250.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);   
}

void Scene_Menu::update() {
    Scene::update();
    for (Entity* e : m_entityManager.getEntities("Dynamic")) {
        if (tulipDirection == 0) {
            e->transformComponent->position.x += 1.0f;
            if (e->transformComponent->position.x >= title->transformComponent->position.x+textBounds.size.x/2+5.0f) {
                tulipDirection = 1;
            }
        } else if (tulipDirection == 1) {
            e->transformComponent->position.y += 1.0f;
            if (e->transformComponent->position.y >= title->transformComponent->position.y+textBounds.size.y/2+5.0f) {
                tulipDirection = 2;
            }
        } else if (tulipDirection == 2) {
            e->transformComponent->position.x -= 1.0f;
            if (e->transformComponent->position.x <= title->transformComponent->position.x-textBounds.size.x/2-32.0f-5.0f) {
                tulipDirection = 3;
            }
        } else if (tulipDirection == 3) {
            e->transformComponent->position.y -=1.0f;
            if (e->transformComponent->position.y <= title->transformComponent->position.y-textBounds.size.y/2-32.0f-5.0f) {
                tulipDirection = 0;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && (!downPressed || m_currentFrame > nextInputTime)) {
        currentSelection = (currentSelection + 1) % 3;
        downPressed = true;
        nextInputTime = m_currentFrame + 20;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        downPressed = false;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && (!upPressed || m_currentFrame > nextInputTime)) {
        currentSelection = (currentSelection - 1 + 3) % 3;
        upPressed = true;
        nextInputTime = m_currentFrame + 20;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        upPressed = false;
    }

    playButton->setHidden(currentSelection != 0);
    shopButton->setHidden(currentSelection != 1);
    quitButton->setHidden(currentSelection != 2);

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Enter)]) {
        if (currentSelection == 0) {
            switchScene("levels");
        } else if (currentSelection == 1) {
            switchScene("shop");
        } else if (currentSelection == 2) {
            exit(0);
        }
    }
}