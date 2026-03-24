#include <SFML/Graphics.hpp>
#include <exception>
#include <string>
#include <vector>
#include "game.hpp"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 640, 480 } ), "PLANTS VS ROBOTS", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	Game game;

	while ( window.isOpen() )
	{
		for (auto& keyState : game.gameData.keyPressed) {
			keyState = false;
		}

		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
			else if (event->is<sf::Event::MouseButtonPressed>())
				game.mousePressed(window);
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				game.gameData.keyPressed[static_cast<std::size_t>(keyPressed->scancode)] = true;
			}
		}

		game.update();
		game.draw(window);
	}
}
