#include "stdafx.h"
#include "Character.h"

CCharacter::CCharacter(const sf::Vector2f & startPoint, std::string spriteFileName, sf::Vector2f rectangleSize, sf::Vector2f origin = {0, 0})
{
	if (!m_texture.loadFromFile(spriteFileName))
		throw std::domain_error("bad texture filename!");

	m_sprite.setTexture(m_texture);
	FillAnimationContainer();
	m_sprite.setTextureRect(m_animationFrames.front());
	m_sprite.setPosition(startPoint);
	m_sprite.setOrigin(origin);

	m_rectangle.left = startPoint.x;
	m_rectangle.top = startPoint.y;
	m_rectangle.width = rectangleSize.x;
	m_rectangle.height = rectangleSize.y;

	m_speed = NORMAL_MOVE_STEP;
}

sf::FloatRect CCharacter::GetRectangle() const
{
	return m_rectangle;
}

sf::Sprite CCharacter::GetSprite() const
{
	return m_sprite;
}

bool CCharacter::CheckCollision(sf::Vector2f position, sf::Vector2f size) const
{
	return (!(
		m_sprite.getPosition().x + (m_rectangle.width / 2)*cos(m_sprite.getRotation() * static_cast<float>(M_PI) / 180) < position.x
		|| m_sprite.getPosition().x + (m_rectangle.width / 2)*cos(m_sprite.getRotation() * static_cast<float>(M_PI) / 180) > position.x + size.x
		|| m_sprite.getPosition().y + (m_rectangle.width / 2)*sin(m_sprite.getRotation() * static_cast<float>(M_PI) / 180) < position.y
		|| m_sprite.getPosition().y + (m_rectangle.width / 2)*sin(m_sprite.getRotation() * static_cast<float>(M_PI) / 180) > position.y + size.y
		));
}

bool CCharacter::CheckCollision(sf::FloatRect rectangle) const
{
	return CheckCollision({ rectangle.left, rectangle.top }, { rectangle.width, rectangle.height });
}

sf::Vector2f CCharacter::GetPosition() const
{
	return m_sprite.getPosition();
}

void CCharacter::Move(const sf::Vector2f & moveParameters)
{
	m_sprite.move(moveParameters);
}

bool CCharacter::TryMoveForward(const std::vector<TmxObject> & barriers)
{
	CCharacter temp = *this;
	temp.MoveForward();
	bool wasCollision = false;
	for (size_t i = 0; i < barriers.size() && !wasCollision; ++i)
	{
		wasCollision = temp.CheckCollision(barriers[i].rect);
	}
	if (!wasCollision)
		this->MoveForward();
	return wasCollision;
}

bool CCharacter::TryRotate(const std::vector<TmxObject> & barriers, float angle)
{
	CCharacter temp = *this;
	temp.Rotate(angle);
	bool wasCollision = false;
	for (size_t i = 0; i < barriers.size() && !wasCollision; ++i)
	{
		wasCollision = temp.CheckCollision(barriers[i].rect);
	}
	if (!wasCollision)
		this->Rotate(angle);
	return wasCollision;
}

sf::Vector2f CCharacter::GetMovingForvardParameters(float angle, float speed)
{
	return { speed*cos(angle * static_cast<float>(M_PI) / 180), speed*sin(angle * static_cast<float>(M_PI) / 180) };
}

void CCharacter::MoveForward()
{
	m_sprite.move(GetMovingForvardParameters(m_sprite.getRotation(), m_speed));
}

void CCharacter::Draw(sf::RenderTarget & target)
{
	target.draw(m_sprite);
}

void CCharacter::FillAnimationContainer()
{
	sf::IntRect temp(0, 0, static_cast<int>(CELL_SIZE.x * 4), static_cast<int>(CELL_SIZE.y * 2));
	sf::Vector2f step{ 0.0f, CAT_SPRITE_HEIGHT };
	m_animationFrames.push_back(temp);

	for (size_t i = 1; i < ANIMATION_FRAMES_NUMBER; ++i)
	{
		temp.left += static_cast<int>(step.x);
		temp.top += static_cast<int>(step.y);
		m_animationFrames.push_back(temp);
	}
}

void CCharacter::UpdateAnimation()
{
	++m_currentAnimationFrame;
	if (m_currentAnimationFrame == m_animationFrames.size())
	{
		m_currentAnimationFrame = 0;
		std::reverse(m_animationFrames.begin(), m_animationFrames.end());
	}
	m_sprite.setTextureRect(m_animationFrames[m_currentAnimationFrame]);
}

void CCharacter::Rotate(float angle)
{
	m_sprite.rotate(angle);
}