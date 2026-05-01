#include "entity.hpp"

Entity::Entity(std::string t) : m_tag(t) {
}

void Entity::draw(sf::RenderWindow& window) {
    if (transformComponent != nullptr) {
        if (spriteComponent != nullptr) {
            sf::Sprite sprite(*spriteComponent->texture);
            sprite.setPosition( transformComponent->position );
            sprite.setScale( transformComponent->scale );
            if (transformComponent->origin == Origin::Center) {
                sf::FloatRect bounds = sprite.getLocalBounds();
                sprite.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2));
            }
            sprite.setRotation(sf::degrees(transformComponent->rotation));

            if (colorComponent != nullptr) {
                sprite.setColor(colorComponent->color);
            }

            window.draw(sprite);
        }
        if (shapeComponent != nullptr) {
            if (shapeComponent->type == ShapeType::Rectangle) {
                sf::RectangleShape rect(sf::Vector2f(shapeComponent->size.x * transformComponent->scale.x, shapeComponent->size.y * transformComponent->scale.y));
                
                if (transformComponent->origin == Origin::Center) {
                    sf::FloatRect bounds = rect.getLocalBounds();
                    rect.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2));
                }

                rect.setPosition(transformComponent->position);
                if (colorComponent != nullptr) {
                    rect.setFillColor(colorComponent->color);
                }

                rect.setRotation(sf::degrees(transformComponent->rotation));

                window.draw(rect);
            } else if (shapeComponent->type == ShapeType::Circle) {
                sf::CircleShape circle(shapeComponent->size.x * transformComponent->scale.x / 2);
                circle.setPosition(transformComponent->position);

                if (colorComponent != nullptr) {
                    circle.setFillColor(colorComponent->color);
                }

                if (transformComponent->origin == Origin::Center) {
                    sf::FloatRect bounds = circle.getLocalBounds();
                    circle.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2));
                }
                circle.setRotation(sf::degrees(transformComponent->rotation));

                window.draw(circle);
            }
        }
        if (textComponent != nullptr) {
            sf::Text text(*textComponent->font);
            text.setString(textComponent->text);
            text.setCharacterSize(textComponent->size);
            text.setStyle(textComponent->style);

            sf::FloatRect bounds = text.getLocalBounds();
            
            if (transformComponent->origin == Origin::Center) {
                    text.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2));
                }

            text.setPosition(sf::Vector2f(
                transformComponent->position.x,
                transformComponent->position.y
            ));

            text.setRotation(sf::degrees(transformComponent->rotation));

            if (colorComponent != nullptr) {
                text.setFillColor( colorComponent->color );
            }

            window.draw(text);
        }
    }
}

void Entity::destroy() {
    m_active = false;
}

size_t Entity::getId() const {
    return m_id;
}

bool Entity::isActive() const {
    return m_active;
}

const std::string& Entity::getTag() const {
    return m_tag;
}

bool Entity::isHidden() const {
    return m_hidden;
}

void Entity::setHidden(bool hidden) {
    m_hidden = hidden;
}