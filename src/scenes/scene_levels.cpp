#include "scene_levels.hpp"
#include "../components.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../util.h"
#include "../game_data.hpp"
#include <iostream>

Scene_Levels::Scene_Levels(GameData* gameData) : Scene(gameData) {
    sf::Font* m_font = m_gameData->font;

    Entity* background = m_entityManager.create("Background");
    background->colorComponent = new Component_Color(sf::Color(255, 255, 255));
    background->transformComponent = new Component_Transform(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 1.0f), 0.0f);
    background->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(640.0f, 480.0f));
}

void Scene_Levels::update() {
    Scene::update();

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Escape)]) {
        switchScene("menu");
    }
}