#pragma once

#include <string>
#include "components.hpp"
#include <SFML/Graphics.hpp>

class Entity {
public:
	Component_Color* colorComponent = nullptr;
	Component_Transform* transformComponent = nullptr;
	Component_Sprite* spriteComponent = nullptr;
	Component_Text* textComponent = nullptr;
	Component_HitBox* hitBoxComponent = nullptr;
	Component_MouseEvent* mouseEventComponent = nullptr;
	Component_Shape* shapeComponent = nullptr;
	Component_Health* healthComponent = nullptr;
	
	Entity(std::string t);
	void draw(sf::RenderWindow& window);
    void destroy();
	size_t getId() const;
	bool isActive() const;
	bool isHidden() const;
	void setHidden(bool hidden);
	const std::string& getTag() const;

	friend class EntityManager;
private:
	size_t m_id;
	bool m_active = true;
	const std::string m_tag;
	bool m_hidden =  false;
};