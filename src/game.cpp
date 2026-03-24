#include "game.hpp"
#include "scenes/scene_menu.hpp"
#include "scenes/scene_levels.hpp"
#include "scenes/scene_shop.hpp"
#include <iostream>

Game::Game() {
    if (!gameData.loadResources()) {
        std::cerr << "Failed to load game resources\n";
    }
    scenes["menu"] = new Scene_Menu(&gameData);
    scenes["levels"] = new Scene_Levels(&gameData);
    scenes["shop"] = new Scene_Shop(&gameData);
    activeScene = "menu";
}

Game::~Game() {
    for (auto& scene : scenes) {
        delete scene.second;
    }
}

void Game::update() {
    if (scenes[activeScene]->getSwitchSceneTo() != "") {
        activeScene = scenes[activeScene]->getSwitchSceneTo();
        scenes[activeScene]->switchScene("");
    }
    
    scenes[activeScene]->update();
}

void Game::draw(sf::RenderWindow& window) {
    scenes[activeScene]->draw(window);
}

void Game::mousePressed(sf::RenderWindow& window) {
    scenes[activeScene]->mousePressed(window);
}