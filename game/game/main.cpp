#include "stdafx.h"
#include "Character.h"
#include "CatPlayer.h"
#include "Barrier.h"

void HandleEventsQueue(sf::RenderWindow & window, CCatPlayer & catPlayer, std::vector<TmxObject> & barriers);
bool HandleKeypress(const sf::Event::KeyEvent & event, CCatPlayer & catPlayer, std::vector<TmxObject> & barriers);
void Update(sf::Clock & clock, CCatPlayer & catPlayer, float & gameTime);

int main()
{
	try
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		sf::Clock clock;
		float timer = 0.0f;
		TmxLevel lvl;
		lvl.LoadFromFile("src/lvl0.tmx");
		CCatPlayer cat({350.0f, 350.0f}, "src/cat.png");

		std::vector<TmxObject> barriers{};
		sf::RenderWindow window(sf::VideoMode(800, 600), "Game", sf::Style::Close, settings);
		sf::View view;
		view.reset(sf::FloatRect(0, 0, 800, 600));
		view.zoom(1);
		while (window.isOpen())
		{
			HandleEventsQueue(window, cat, barriers);

			Update(clock, cat, timer);
			window.clear();
			window.setView(view);

			view.setCenter(cat.GetPosition());
			lvl.Draw(window);
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

void HandleEventsQueue(sf::RenderWindow & window, CCatPlayer & catPlayer, std::vector<TmxObject> & barriers)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		else if ((event.type == sf::Event::KeyPressed))
		{
			HandleKeypress(event.key, catPlayer, barriers);
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

bool HandleKeypress(const sf::Event::KeyEvent & event, CCatPlayer & catPlayer, std::vector<TmxObject> & barriers)
{
	bool handled = true;
	if (event.code == sf::Keyboard::Up)
	{
		catPlayer.TryMoveForward(barriers);
	}
	else if (event.code == sf::Keyboard::Left)
	{
		catPlayer.TryRotate(barriers, -1*CAT_ROTATION_SPEED);
	}
	else if (event.code == sf::Keyboard::Right)
	{
		catPlayer.TryRotate(barriers, CAT_ROTATION_SPEED);
	}
	else
		handled = false;
	return handled;
}