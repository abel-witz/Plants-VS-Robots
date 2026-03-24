#pragma once

#include <string>
#include <map>
#include "scene.hpp"
#include "game_data.hpp"

class Scene;

class Game {
public:
    GameData gameData;
    std::map<std::string, Scene*> scenes;
    std::string activeScene;

    Game();
    void update();
    void draw(sf::RenderWindow& window);
    void mousePressed(sf::RenderWindow& window);
    void mousePressed();
    ~Game();
};