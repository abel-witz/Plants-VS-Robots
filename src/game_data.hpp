#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class GameData {
public:
    sf::Font* font = nullptr;
    sf::Texture* tulipTexture = nullptr;
    std::array<bool, sf::Keyboard::ScancodeCount> keyPressed;

    GameData();
    ~GameData();

    bool loadResources();
};