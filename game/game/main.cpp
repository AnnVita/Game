// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TmxLevel.h"

void HandleEventsQueue(sf::RenderWindow & window);

int main()
{
	try
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		sf::RenderWindow window(sf::VideoMode(800, 600), "Game", sf::Style::Close, settings);

		TmxLevel level;
		level.LoadFromFile("src/platformer.tmx");

		while (window.isOpen())
		{
			HandleEventsQueue(window);

			level.Draw(window);

			window.display();
		}


	}
	catch (const std::exception & ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}

void HandleEventsQueue(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}