#pragma once

#include "entity_manager.hpp"

class GameData;

class Scene {
private:
	std::string m_switchSceneTo = "";

protected:
	EntityManager m_entityManager;
	bool m_firstFrame = true;
	unsigned long int m_currentFrame = 0;
	GameData* m_gameData = nullptr;

public:
	Scene(GameData* gameData = nullptr);

	virtual void update();
	void draw(sf::RenderWindow& window) const;
	void mousePressed(sf::RenderWindow& window);
	void switchScene(const std::string& sceneName);
	const std::string& getSwitchSceneTo() const;
};