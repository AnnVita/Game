#include "stdafx.h"
#include "Character.h"
#include "CatPlayer.h"
#include "Barrier.h"

void HandleEventsQueue(sf::RenderWindow & window, CCatPlayer & catPlayer, CBarrier & barrier);
bool HandleKeypress(const sf::Event::KeyEvent & event, CCatPlayer & catPlayer, CBarrier & barrier);
void Update(sf::Clock & clock, CCatPlayer & catPlayer, float & gameTime);

int main()
{
	try
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		sf::Clock clock;
		float timer = 0.0f;

		CCatPlayer cat({0.0f, 0.0f}, "src/cat.png");
		CBarrier barrier(sf::FloatRect(200.0f, 200.0f, 100.0f, 100.0f));
		sf::RenderWindow window(sf::VideoMode(800, 600), "Game", sf::Style::Close, settings);

		while (window.isOpen())
		{
			window.clear();

			HandleEventsQueue(window, cat, barrier);

			Update(clock, cat, timer);

			barrier.Draw(window);
			cat.Draw(window);

			window.display();
		}
	}
	catch (const std::exception & ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return EXIT_SUCCESS;
}

void HandleEventsQueue(sf::RenderWindow & window, CCatPlayer & catPlayer, CBarrier & barrier)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		else if ((event.type == sf::Event::KeyPressed))
		{
			HandleKeypress(event.key, catPlayer, barrier);
		}
	}
}

void Update(sf::Clock & clock, CCatPlayer & catPlayer, float & gameTime)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	gameTime += elapsedTime;
	clock.restart();
	if (gameTime > ITER_TIME)
	{
		gameTime = 0;
		catPlayer.UpdateAnimation();
	}
}

bool HandleKeypress(const sf::Event::KeyEvent & event, CCatPlayer & catPlayer, CBarrier & barrier)
{
	bool handled = true;
	if (!catPlayer.CheckCollision(barrier.GetLocation(), barrier.GetSize()))
	{
		if (event.code == sf::Keyboard::Up)
		{
			catPlayer.MoveForward(Direction::UP);
		}
		else if (event.code == sf::Keyboard::Left)
		{
			catPlayer.MoveForward(Direction::LEFT);
		}
		else if (event.code == sf::Keyboard::Right)
		{
			catPlayer.MoveForward(Direction::RIGHT);
		}
		else if (event.code == sf::Keyboard::Down)
		{
			catPlayer.MoveForward(Direction::DOWN);
		}
		else
			handled = false;
	}
	else
		handled = false;
	return handled;
}