#include "scene.hpp"

Scene::Scene(GameData* gameData) : m_gameData(gameData) {
}

void Scene::update() {
    if (!m_firstFrame) {
        m_currentFrame++;
    }
    m_firstFrame = false;
    m_entityManager.update();
}

void Scene::draw(sf::RenderWindow& window) const {
    window.clear();
    for (Entity* e : m_entityManager.getEntities()) {
        if (!e->isHidden()) {
            e->draw(window);
        }
    }
    window.display();
}

void Scene::mousePressed(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
    for (Entity* e : m_entityManager.getEntities()) {
        if (e->hitBoxComponent != nullptr && e->transformComponent != nullptr) {
            sf::FloatRect hitBox;

            if (e->transformComponent->origin == Origin::Center) {
                hitBox = sf::FloatRect(
                    sf::Vector2f(e->transformComponent->position.x - e->hitBoxComponent->size.x*e->transformComponent->scale.x / 2,
                    e->transformComponent->position.y - e->hitBoxComponent->size.y*e->transformComponent->scale.y / 2),
                    sf::Vector2f(e->hitBoxComponent->size.x*e->transformComponent->scale.x,
                    e->hitBoxComponent->size.y*e->transformComponent->scale.y)
                );
            } else {
                hitBox = sf::FloatRect(
                    sf::Vector2f(e->transformComponent->position.x,
                    e->transformComponent->position.y),
                    sf::Vector2f(e->hitBoxComponent->size.x*e->transformComponent->scale.x,
                    e->hitBoxComponent->size.y*e->transformComponent->scale.y)
                );
            }

            if (hitBox.contains(sf::Vector2f(mousePos))) {
                if (e->mouseEventComponent != nullptr && e->mouseEventComponent->onMousePress != nullptr) {
                    e->mouseEventComponent->onMousePress();
                }
            }
        }
    }
}

void Scene::switchScene(const std::string& sceneName) {
    m_switchSceneTo = sceneName;
}

const std::string& Scene::getSwitchSceneTo() const {
    return m_switchSceneTo;
}