#include "scene_game.hpp"
#include "../components.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../util.h"
#include "../game_data.hpp"
#include <string>

Scene_Game::Scene_Game(GameData* gameData) : Scene(gameData) {
    sf::Font* font = m_gameData->font;
}

void Scene_Game::update() {
    Scene::update();

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Escape)]) {
        switchScene("levels");
    }
}