#include "game_data.hpp"
#include <iostream>

GameData::GameData() {
}

GameData::~GameData() {
    delete font;
    delete tulipTexture;
}

bool GameData::loadResources() {
    font = new sf::Font("../../../assets/fonts/Jersey10-Regular.ttf");
    if (font->getInfo().family.empty()) {
        std::cerr << "Failed to load font\n";
        delete font;
        font = nullptr;
        return false;
    }

    tulipTexture = new sf::Texture("../../../assets/img/Plants/Tulips.png");
    if (tulipTexture->getSize().x == 0) {
        std::cerr << "Failed to load tulip texture\n";
        delete tulipTexture;
        tulipTexture = nullptr;
        return false;
    }

    return true;
}
