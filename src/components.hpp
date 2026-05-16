#pragma once

#include <SFML/Graphics.hpp>
#include <string>

enum ShapeType {
	Rectangle,
	Circle,
};

enum Origin {
	TopLeft,
	Center,
};

class Component_Color {
public:
	sf::Color color;
	
	Component_Color() : color(sf::Color::White) {}
	Component_Color(sf::Color c) : color(c) {}
};

class Component_Transform {
public:
	sf::Vector2f position;
	sf::Vector2f scale;
	sf::Vector2f velocity;
	float rotation;
	Origin origin;
	
	Component_Transform() 
		: position(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f), origin(Origin::TopLeft) {}
	Component_Transform(sf::Vector2f pos, sf::Vector2f scl, float rot = 0.0f, Origin orig = Origin::TopLeft)
		: position(pos), scale(scl), rotation(rot), origin(orig) {}
};

class Component_Sprite {
public:
	sf::Texture* texture;
	
	Component_Sprite() : texture(nullptr) {}
	Component_Sprite(sf::Texture* t) : texture(t) {}
};

class Component_Text {
public:
	sf::Font* font;
	std::string text;
	unsigned int size;
	sf::Text::Style style;
	
	Component_Text() : font(nullptr), text(""), size(12), style(sf::Text::Regular) {}
	Component_Text(sf::Font* f, const std::string& t, unsigned int s, sf::Text::Style st = sf::Text::Regular) 
		: font(f), text(t), size(s), style(st) {}
};

class Component_HitBox {
public:
	sf::Vector2f size;
	
	Component_HitBox() : size(0.0f, 0.0f) {}
	Component_HitBox(sf::Vector2f s) : size(s) {}
};

class Component_MouseEvent {
public:
	void (*onMousePress)();
	
	Component_MouseEvent() : onMousePress(nullptr) {}
	Component_MouseEvent(void (*func)()) : onMousePress(func) {}
};


class Component_Shape {
public:
    ShapeType type;
    sf::Vector2f size;

	Component_Shape() : type(ShapeType::Rectangle), size(0.0f, 0.0f) {}
	Component_Shape(ShapeType t, sf::Vector2f s) : type(t), size(s) {}
};

class Component_Health {
public:
    int hp; 
    Component_Health() : hp(10) {}
    Component_Health(int h) : hp(h) {}
};