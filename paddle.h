#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/Window.hpp>

#include <SFML/Audio.hpp>

#include <SFML/Network.hpp>

#include <SFML/System.hpp>

#include <SFML/OpenGL.hpp>

#include <SFML/Main.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include "global.h"

using namespace std;

using namespace sf;

class Paddle
{
public:


	Vector2f position;

	RectangleShape paddle;




	float batSpeed = 0.3f;

	Paddle(float startx, float starty);

	FloatRect getPosition();

	RectangleShape getpaddle();

	void paddle_update(float dt);

};
