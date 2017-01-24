#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include "TmxLevel.h"
#include <memory>
#include <vector>
#include <algorithm>

#define _USE_MATH_DEFINES  
#include <cmath> 
#include <math.h>  

static const size_t MAX_HEALTH = 1000;
static const std::string CAT_TEXTURE_FILE = "src/cat.png";
static const sf::Vector2f CELL_SIZE{16, 16};
static const float NORMAL_MOVE_STEP = 2.0f;
static const float ITER_TIME = 0.1f;
static const size_t ANIMATION_FRAMES_NUMBER = 8;
static const float CAT_SPRITE_HEIGHT = CELL_SIZE.x * 2;
static const float CAT_SPRITE_WIDTH = CELL_SIZE.x * 4;
static const float CAT_ROTATION_SPEED = 4;
static const sf::Vector2f CAT_ORIGIN{CELL_SIZE.x * 2, CELL_SIZE.x};

enum class Direction
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};