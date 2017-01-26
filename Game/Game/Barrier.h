#pragma once

class CBarrier
{
public:
	CBarrier(sf::FloatRect barrier);
	sf::Vector2f GetLocation() const;
	sf::Vector2f GetSize() const;

	void Draw(sf::RenderTarget & target);
private:
	sf::RectangleShape m_rectangle;
};