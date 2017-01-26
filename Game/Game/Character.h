#pragma once
#include "stdafx.h"

class CCharacter
{
public:
	CCharacter(const sf::Vector2f & startPoint, std::string spriteFileName, sf::Vector2f rectangleSize, sf::Vector2f origin);
	virtual ~CCharacter() = default;

	sf::FloatRect GetRectangle() const;
	sf::Sprite GetSprite() const;

	bool CheckCollision(sf::Vector2f position, sf::Vector2f size) const;
	bool CheckCollision(sf::FloatRect rectangle) const;

	sf::Vector2f GetPosition() const;

	void Move(const sf::Vector2f & moveParameters);
	void MoveForward(Direction direction);

	virtual void Draw(sf::RenderTarget & target);
	void UpdateAnimation();

private:
	void FillAnimationContainer();

	sf::FloatRect m_rectangle;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::vector<sf::IntRect> m_animationFrames;
	size_t m_currentAnimationFrame = 0;
	Direction m_direction;
	float m_speed;
};