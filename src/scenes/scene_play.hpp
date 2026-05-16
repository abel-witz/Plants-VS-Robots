#pragma once

#include "../scene.hpp"
#include <vector> // hyper important pour notre liste de robots

class Scene_Play : public Scene {
public:
    Scene_Play(GameData* gameData = nullptr);
    void loadLevel(); // LA NOUVELLE FONCTION
    void update() override;

// les anciennes fonctions 
    void spawnPlant(float x, float y);
    void spawnRobot(int type, float x, float y);

// === NOUVELLES FONCTIONS MODULABLES ===
    // pour planter direct dans une case (ex: col 2, ligne 0)
    void spawnPlantGrid(int gridX, int gridY); 
    // pour faire apparaitre un robot direct au bout d'une ligne precise
    void spawnRobotRow(int type, int row);

private:
// les reglages modulables du plateau
    int m_numRows;    // modulable selon le niveau (1 pour le niveau 1)
    int m_numCols;    // generalement 9
    float m_tileSize; // 50.0f
    float m_startX;   // 95.0f
    float m_startY;   // 200.0f

// le systeme de vagues
    std::vector<int> m_robotQueue; // liste des types de robots (0, 1, 0, 2...)
    sf::Clock m_waveClock;         // chrono pour espacer les apparitions
};