#include "scene_play.hpp"
#include "../components.hpp"
#include "../entity.hpp"
#include "../game_data.hpp"
#include <iostream>
#include <fstream> 
#include <sstream> 

sf::Clock shootClock;

// constructeur vide mnt c est dans loadLevel
Scene_Play::Scene_Play(GameData* gameData) : Scene(gameData) {
}

//la grosse fct pour recharger la map pr chak nivo
void Scene_Play::loadLevel() {
 // netoyage de bourin des vieilles entités
    for (auto& entity : m_entityManager.getEntities()) {
        entity->destroy();
    }
    m_robotQueue.clear();

//valeurs par defaut au cas ou
    m_numCols = 9;
    m_tileSize = 720.f / 7;
    m_startX = m_tileSize;
    m_startY = m_tileSize * 2;
    m_numRows = 5; 

 // LISTE TEMPORAIRE PR RETENIR LES PLANTES A FAIRE POP
    std::vector<std::pair<int, int>> plantsToSpawn;

 //lecture du ficher .txt du nivo
    std::string levelPath = "assets/levels/level" + std::to_string(m_gameData->currentLevel) + ".txt";
    std::ifstream file(levelPath);
    
    if (!file.is_open()) {
        std::cerr << "Erreur: jarrive pas a lire " << levelPath << "\n";
    } else {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string command;
            ss >> command;
            
            if (command == "ROWS") {
                ss >> m_numRows;
            } else if (command == "WAVE") {
                int robotType;
                while (ss >> robotType) {
                    m_robotQueue.push_back(robotType);
                }
            } else if (command == "PLANT") {
                int plantType, gridX, gridY;
                ss >> plantType >> gridX >> gridY;
                // on memorise les coordonees pour plus tard au lieu de creer lentite sous la map
                plantsToSpawn.push_back({gridX, gridY});
            }
        }
    }

 // bg sombre deriere
    Entity* bg = m_entityManager.create("Background");
    bg->colorComponent = new Component_Color(sf::Color(20, 20, 20)); 
    bg->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(1280.0f, 720.0f));
    bg->transformComponent = new Component_Transform(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1.0f, 1.0f), 0.0f);

 // la maison carre en haut a gauche
    Entity* house = m_entityManager.create("Static");
    house->colorComponent = new Component_Color(sf::Color(139, 69, 19)); 
    house->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(80.0f, 80.0f)); 
    house->transformComponent = new Component_Transform(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(1.0f, 1.0f), 0.0f);

// damier vert generer selon numRows du .txt
    for (int row = 0; row < m_numRows; row++) {
        for (int col = 0; col < m_numCols; col++) {
            Entity* tile = m_entityManager.create("Tile");
            sf::Color tileColor = ((row + col) % 2 == 0) ? sf::Color(34, 139, 34) : sf::Color(50, 205, 50);
            tile->colorComponent = new Component_Color(tileColor);
            tile->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(m_tileSize - 2.0f, m_tileSize - 2.0f)); 
            float px = m_startX + col * m_tileSize;
            float py = m_startY + row * m_tileSize;
            tile->transformComponent = new Component_Transform(sf::Vector2f(px, py), sf::Vector2f(1.0f, 1.0f), 0.0f);
        }
    }

    for (int row = 0; row < 720 / m_tileSize; row++) {
        Entity *tile = m_entityManager.create("Tile");
        sf::Color tileColor = (row % 2 == 1) ? sf::Color(179, 90, 0) : sf::Color(204, 102, 0);
         tile->colorComponent = new Component_Color(tileColor);
        tile->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(m_tileSize - 2.0f, m_tileSize - 2.0f)); 
        float px = 0;
        float py = row * m_tileSize;
        tile->transformComponent = new Component_Transform(sf::Vector2f(px, py), sf::Vector2f(1.0f, 1.0f), 0.0f);
    }

// barre dinventaire mincraft en ba
    float barStartX = 515.0f; 
    for (int i = 0; i < 5; i++) {
        Entity* slot = m_entityManager.create("HUD_Slot");
        sf::Color slotColor = (i == 0) ? sf::Color(200, 200, 200) : sf::Color(80, 80, 80);
        slot->colorComponent = new Component_Color(slotColor);
        slot->shapeComponent = new Component_Shape(ShapeType::Rectangle, sf::Vector2f(40.0f, 40.0f));
        slot->transformComponent = new Component_Transform(sf::Vector2f(barStartX + i * 50.0f, 650.0f), sf::Vector2f(1.0f, 1.0f), 0.0f);
    }
    
// Maintenant on fait spawner les plantes par dessus l'herbe !
    for (auto& p : plantsToSpawn) {
        spawnPlantGrid(p.first, p.second);
    }
    
    m_waveClock.restart();
    shootClock.restart();
}

// ==== FONCTIONS GRILLE ABSTRACT ====

void Scene_Play::spawnPlantGrid(int gridX, int gridY) {
    // on check si on est pas en deor
    if (gridX < 0 || gridX >= m_numCols || gridY < 0 || gridY >= m_numRows) return;
    
    float px = m_startX + gridX * m_tileSize + m_tileSize / 2;
    float py = m_startY + gridY * m_tileSize + m_tileSize / 2;
    
    spawnPlant(px, py);
}

void Scene_Play::spawnRobotRow(int type, int row) {
    if (row < 0 || row >= m_numRows) return;
    
// spawn tou a droite du screen
    float px = 1280.0f; 
    float py = m_startY + row * m_tileSize + m_tileSize / 2;
    
    spawnRobot(type, px, py);
}

// ==== FONCTIONS DE SPAWN PHYSIQUE ====

void Scene_Play::spawnPlant(float x, float y) {
    Entity* plant = m_entityManager.create("Plant");
    plant->spriteComponent = new Component_Sprite(m_gameData->tulipTexture);
    plant->transformComponent = new Component_Transform(sf::Vector2f(x, y), sf::Vector2f(2.0f, 2.0f), 0.0f, Origin::Center); 
    plant->hitBoxComponent = new Component_HitBox(sf::Vector2f(40.0f, 40.0f));
}

void Scene_Play::spawnRobot(int type, float x, float y) {
    Entity* robot = m_entityManager.create("Robot");
    
    float speed = 0.0f; 
    int hp = 0;
    sf::Texture* robotTex = nullptr;

    if (type == 0) {
        robotTex = m_gameData->grayRobotTexture;
        speed = 0.5f; 
        hp = 5;
    } else if (type == 1) {
        robotTex = m_gameData->yellowRobotTexture;
        speed = 1.2f; 
        hp = 3; 
    } else if (type == 2) {
        robotTex = m_gameData->tankRobotTexture;
        speed = 0.2f;
        hp = 15;
    }

    robot->spriteComponent = new Component_Sprite(robotTex);
    
// on reduit a fond l'image ia et on rmonte legerement pr centrer
    robot->transformComponent = new Component_Transform(sf::Vector2f(x, y), sf::Vector2f(0.04f, 0.04f), 0.0f, Origin::Center);
    robot->transformComponent->velocity = sf::Vector2f(-speed, 0.0f);
    robot->healthComponent = new Component_Health(hp);
    
 // grosse hitbox generique pr tout les mob pour pas s'embeter ak les collisions
    robot->hitBoxComponent = new Component_HitBox(sf::Vector2f(40.0f, 50.0f));
}

void spawnProjectile(EntityManager& entityManager, sf::Vector2f pos) {
    Entity* projectile = entityManager.create("Projectile");
    projectile->colorComponent = new Component_Color(sf::Color::Green);
    projectile->shapeComponent = new Component_Shape(ShapeType::Circle, sf::Vector2f(10.0f, 10.0f)); 
    
 // cale sur le centre du pot d la tulipe
    projectile->transformComponent = new Component_Transform(sf::Vector2f(pos.x, pos.y), sf::Vector2f(1.0f, 1.0f), 0.0f, Origin::Center);
    projectile->transformComponent->velocity = sf::Vector2f(3.0f, 0.0f);
    projectile->hitBoxComponent = new Component_HitBox(sf::Vector2f(10.0f, 10.0f));
}

// ==== BOUCLE DE JEU ====

void Scene_Play::update() {
 // on reload direct si besoin dapres l'ecran niveau
    if (m_gameData->needReload) {
        loadLevel();
        m_gameData->needReload = false; 
        return; 
    }

    Scene::update(); 

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Escape)]) {
        switchScene("levels");
    }
    
    auto& entities = m_entityManager.getEntities();
    
 // logique des touche pr select ds la barre
    static int currentSelectedSlot = 0; 

    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Num1)]) currentSelectedSlot = 0;
    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Num2)]) currentSelectedSlot = 1;
    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Num3)]) currentSelectedSlot = 2;
    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Num4)]) currentSelectedSlot = 3;
    if (m_gameData->keyPressed[static_cast<std::size_t>(sf::Keyboard::Scancode::Num5)]) currentSelectedSlot = 4;

    int currentSlotIdx = 0;
    for (auto& entity : entities) {
        if (entity->getTag() == "HUD_Slot") {
            if (currentSlotIdx == currentSelectedSlot) {
                entity->colorComponent->color = sf::Color(200, 200, 200); 
            } else {
                entity->colorComponent->color = sf::Color(80, 80, 80); 
            }
            currentSlotIdx++;
        }
    }

// === CODE SOURIS / CLAVIER TERMINE : PLACE AU GESTIONNAIRE DE VAGUES ===
// On fait pop un robot de la liste toutes les 1.5 secondes
    if (m_waveClock.getElapsedTime().asSeconds() >= 1.5f) {
        if (!m_robotQueue.empty()) {
            // on recupere le type du premier robot de la file//
            int nextRobotType = m_robotQueue.front();
            
            // on choisi une ligne au pif parmis les lignes dispo du niveau
            int randomRow = rand() % m_numRows;
            
            // on l'envoi sur la piste !
            spawnRobotRow(nextRobotType, randomRow);
            
            // on vire le robot de la file d'attente pr pas kil revienne
            m_robotQueue.erase(m_robotQueue.begin());
            
            std::cout << "Un robot pop ! Il en reste " << m_robotQueue.size() << " en reserve.\n";
        }
        m_waveClock.restart();
    }
// === FIN DU GESTIONNAIRE DE VAGUES ===

 // deplacement et clean d balle perud
    for (auto& entity : entities) {
        if (!entity->isActive()) continue;

        if (entity->transformComponent) {
            entity->transformComponent->position += entity->transformComponent->velocity;
            
            if (entity->getTag() == "Projectile" && entity->transformComponent->position.x > 1280.0f) {
                entity->destroy();
            }
        }
    }
    
// tir ooto
    if (shootClock.getElapsedTime().asSeconds() >= 1.0f) {
        for (auto& entity : entities) {
            if (entity->isActive() && entity->getTag() == "Plant") {
                spawnProjectile(m_entityManager, entity->transformComponent->position);
            }
        }
        shootClock.restart();
    }
    
 // collision avec AABB de base
    for (auto& projectile : entities) {
        if (!projectile->isActive() || projectile->getTag() != "Projectile") continue; 
        
        for (auto& robot : entities) {
            if (!robot->isActive() || robot->getTag() != "Robot") continue; 
            
            if (projectile->transformComponent && robot->transformComponent && 
                projectile->hitBoxComponent && robot->hitBoxComponent) {
                
                sf::Vector2f pPos = projectile->transformComponent->position;
                sf::Vector2f pSize = projectile->hitBoxComponent->size;
                sf::Vector2f rPos = robot->transformComponent->position;
                sf::Vector2f rSize = robot->hitBoxComponent->size;
                
                bool isColliding = (
                    pPos.x < rPos.x + rSize.x &&
                    pPos.x + pSize.x > rPos.x &&
                    pPos.y < rPos.y + rSize.y &&
                    pPos.y + pSize.y > rPos.y
                );
                
                if (isColliding) {
                    projectile->destroy(); 
                    if (robot->healthComponent) {
                        robot->healthComponent->hp -= 1; 
                        if (robot->healthComponent->hp <= 0) {
                            robot->destroy(); 
                            std::cout << "un moob en moins !\n";
                        }
                    }
                }
            }
        }
    }
}