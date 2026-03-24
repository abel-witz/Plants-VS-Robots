#pragma once

#include "../scene.hpp"

class Scene_Shop : public Scene {
public:
	Scene_Shop(GameData* gameData = nullptr);

	void update() override;
	~Scene_Shop();
};