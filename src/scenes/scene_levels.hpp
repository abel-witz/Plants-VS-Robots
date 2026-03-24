#pragma once

#include "../scene.hpp"

class Scene_Levels : public Scene {
public:
	Scene_Levels(GameData* gameData = nullptr);

	void update() override;
	~Scene_Levels();
};