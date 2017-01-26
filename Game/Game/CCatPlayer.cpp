#include "stdafx.h"
#include "CatPlayer.h"

CCatPlayer::CCatPlayer(const sf::Vector2f & startPoint, std::string spriteFileName)
	: CCharacter(startPoint, spriteFileName, CAT_RECTANGLE_SIZE, CAT_ORIGIN)
{
};

