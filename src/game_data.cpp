#include "game_data.hpp"
#include <iostream>

GameData::GameData() {
}

GameData::~GameData() {
    delete font;
    delete tulipTexture;
// netoyage classique
    delete grayRobotTexture;
    delete yellowRobotTexture;
    delete tankRobotTexture;
}

bool GameData::loadResources() {
// le font
    font = new sf::Font("assets/fonts/Jersey10-Regular.ttf");
    if (font->getInfo().family.empty()) {
        std::cerr << "Failed to load font\n";
        delete font; font = nullptr; return false;
    }

// la tulipe
    tulipTexture = new sf::Texture("assets/img/Plants/Tulips.png");
    if (tulipTexture->getSize().x == 0) {
        std::cerr << "Failed to load tulip texture\n";
        delete tulipTexture; tulipTexture = nullptr; return false;
    }

// chargement normal depuis les fichiers png transparent
    grayRobotTexture = new sf::Texture();
    if (!grayRobotTexture->loadFromFile("assets/img/robots/gray.png")) {
        std::cerr << "impossible de lire gray.png\n";
        return false;
    }
    
    yellowRobotTexture = new sf::Texture();
    if (!yellowRobotTexture->loadFromFile("assets/img/robots/yellow.png")) {
        std::cerr << "impossible de lire yellow.png\n";
        return false;
    }
    
    tankRobotTexture = new sf::Texture();
    if (!tankRobotTexture->loadFromFile("assets/img/robots/tank.png")) {
        std::cerr << "impossible de lire tank.png\n";
        return false;
    }

    return true;
}