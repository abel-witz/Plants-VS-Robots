#pragma once

#include "../scene.hpp"

class Scene_Levels : public Scene {
public:
	Entity* m_title;
	Entity* m_scrollBackground;
	Entity* m_scroll;
	Entity* m_levelLabels[10];
	Entity* m_levelButtons[10];

	int m_firstVisibleLevel = 0;
	int m_selectedLevel = 0;

	Scene_Levels(GameData* gameData = nullptr);

	void update() override;
	~Scene_Levels();
};