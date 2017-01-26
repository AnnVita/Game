#include "stdafx.h"
#include "Barrier.h"

CBarrier::CBarrier(sf::FloatRect barrier)
{
	m_rectangle.setPosition(barrier.left, barrier.top);
	m_rectangle.setSize({ barrier.width, barrier.height });

	m_rectangle.setFillColor({ 240, 255, 240 });
}

sf::Vector2f CBarrier::GetLocation() const
{
	return m_rectangle.getPosition();
}

sf::Vector2f CBarrier::GetSize() const
{
	return m_rectangle.getSize();
}

void CBarrier::Draw(sf::RenderTarget & target)
{
	target.draw(m_rectangle);
}