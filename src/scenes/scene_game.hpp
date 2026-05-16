#pragma once

#include "../scene.hpp"

class Scene_Game : public Scene {
public:
	Scene_Game(GameData* gameData = nullptr);

	void update() override;
	~Scene_Game();
};