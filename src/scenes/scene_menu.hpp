#pragma once

#include "../scene.hpp"

class Scene_Menu : public Scene {
private:
	int tulipDirection = 0;
	sf::FloatRect textBounds;

	int currentSelection = 0;
	bool downPressed = false;
	bool upPressed = false;
	
	Entity* title;
	Entity* playButton;
	Entity* shopButton;
	Entity* quitButton;
	unsigned long int nextInputTime = 0;

public:
	Scene_Menu(GameData* gameData = nullptr);

	void update() override;
	~Scene_Menu();
};