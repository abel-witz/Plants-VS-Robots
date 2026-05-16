#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class GameData {
public:
    sf::Font* font = nullptr;
    sf::Texture* tulipTexture = nullptr;
    
    // === NOUVELLES TEXTURES POUR TES ROBOTS ===
    sf::Texture* grayRobotTexture = nullptr;
    sf::Texture* yellowRobotTexture = nullptr;
    sf::Texture* tankRobotTexture = nullptr;
    
    //la variable qui retient le numero du niveau entre les scenes
    int currentLevel = 1;
    bool needReload = true;
    
    std::array<bool, sf::Keyboard::ScancodeCount> keyPressed;

    GameData();
    ~GameData();

    bool loadResources();
};