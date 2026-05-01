#pragma once

#include "../scene.hpp"

class Scene_Menu : public Scene {
private:
	int m_tulipDirection = 0;
	sf::FloatRect m_textBounds;

	int m_currentSelection = 0;
	bool m_downPressed = false;
	bool m_upPressed = false;
	
	Entity* m_title;
	Entity* m_playButton;
	Entity* m_shopButton;
	Entity* m_quitButton;
	unsigned long int m_nextInputTime = 0;

public:
	Scene_Menu(GameData* gameData = nullptr);

	void update() override;
	~Scene_Menu();
};