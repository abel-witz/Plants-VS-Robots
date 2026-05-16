#include "scene_levels.hpp"
#include "../components.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../util.h"
#include "../game_data.hpp"
#include <iostream>
#include <string>

Scene_Levels::Scene_Levels(GameData* gameData) : Scene(gameData) {
    sf::Font* font = m_gameData->font;

    m_selectedLevel = 0;
    m_firstVisibleLevel = 0;

    Entity* background = m_entityManager.create("Background");
    background->colorComponent = new Component_Color(sf::Color(255, 255, 255));
    background->transformComponent = new Component_Transform(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 1.0f), 0.0f);
    // on passe le fond en 1280x720
    background->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(1280.0f, 720.0f));

    m_title = m_entityManager.create("Text");
    m_title->colorComponent = new Component_Color(sf::Color::Black);
    m_title->textComponent = new Component_Text(font, "Levels", 48, sf::Text::Underlined);
    // le nouveau centre c'est 640 mnt
    m_title->transformComponent = new Component_Transform(
        sf::Vector2f(640.f, 70.f),
        sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);

    for (int i=0; i<10; i++) {
        sf::FloatRect bounds = getTextSize("Level " + std::to_string(i+1), font, 40);

        m_levelButtons[i] = m_entityManager.create("Button");
        m_levelButtons[i]->colorComponent = new Component_Color(sf::Color::Green);
        // centre les boutons a 640
        m_levelButtons[i]->transformComponent = new Component_Transform(
            sf::Vector2f(640.0f, 0.0f),
            sf::Vector2f(1.1f, 1.3f), 0.0f, Origin::Center);
        m_levelButtons[i]->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(bounds.size.x, bounds.size.y));

        m_levelLabels[i] = m_entityManager.create("Label");
        m_levelLabels[i]->colorComponent = new Component_Color(sf::Color::Black);
        m_levelLabels[i]->textComponent = new Component_Text(font, "Level " + std::to_string(i+1), 40);
        // centre les textes a 640
        m_levelLabels[i]->transformComponent = new Component_Transform(
            sf::Vector2f(640.0f, 0.0f),
            sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);
    }

    m_scrollBackground = m_entityManager.create("Static");
    m_scrollBackground->colorComponent = new Component_Color(sf::Color(128, 128, 128));
    m_scrollBackground->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(10.0f, 45.0f*4));
    // on decale la tite barre de scroll sur la droite
    m_scrollBackground->transformComponent = new Component_Transform(
            sf::Vector2f(640.0f+150.0f, 132.0f),
            sf::Vector2f(1.0f, 1.0f), 0.0f);

    m_scroll = m_entityManager.create("Dynamic");
    m_scroll->colorComponent = new Component_Color(sf::Color::Black);
    m_scroll->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(10.0f, 45.0f*(10.0f/4.0f)));
    m_scroll->transformComponent = new Component_Transform(
            sf::Vector2f(640.0f+150.0f, 0.0f),
            sf::Vector2f(1.0f, 1.0f), 0.0f);
}

void Scene_Levels::update() {
    Scene::update();

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Enter)]) {
        m_gameData->currentLevel = m_selectedLevel + 1;
        m_gameData->needReload = true; // on dit a la scene Play de tout peter et recommencer
        switchScene("play");
    }

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Escape)]) {
        switchScene("menu");
    }

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Enter)]) {
        switchScene("play");
    }

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Down)]) {
        if (m_selectedLevel != 9) {
            m_selectedLevel += 1;
            if (m_selectedLevel == m_firstVisibleLevel + 4) {
                m_firstVisibleLevel += 1;
            }
        }
    }

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Up)]) {
        if (m_selectedLevel != 0) {
            m_selectedLevel -= 1;
            if (m_selectedLevel == m_firstVisibleLevel - 1) {
                m_firstVisibleLevel -= 1;
            }
        }
    }

    for (int i=0; i<10; i++) {
        m_levelButtons[i]->setHidden(i != m_selectedLevel);
        m_levelLabels[i]->setHidden(!(i >= m_firstVisibleLevel && i < m_firstVisibleLevel + 4));
        m_levelButtons[i]->transformComponent->position.y = 150.0f + 50.0f * (i-m_firstVisibleLevel);
        m_levelLabels[i]->transformComponent->position.y = 150.0f + 50.0f * (i-m_firstVisibleLevel);
    }

    m_scroll->transformComponent->position.y = 132.0f + (m_firstVisibleLevel / 4.0f) * 45.0f;
    
}