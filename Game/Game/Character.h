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

	bool TryMoveForward(const std::vector<TmxObject> & barriers);
	bool TryRotate(const std::vector<TmxObject> & barriers, float angle);
	void MoveForward();
	void Rotate(float angle);

	virtual void Draw(sf::RenderTarget & target);
	void UpdateAnimation();

private:
	void FillAnimationContainer();
	void Move(const sf::Vector2f & moveParameters);
	static sf::Vector2f GetMovingForvardParameters(float angle, float speed);
	static CheckCollision(sf::Vector2f & firstBodyPosition, sf::Vector2f & firstBodySize, float firstBodyRotationAngle, const sf::FloatRect & rect);

	sf::FloatRect m_rectangle;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::vector<sf::IntRect> m_animationFrames;
	size_t m_currentAnimationFrame = 0;
	float m_speed;
};