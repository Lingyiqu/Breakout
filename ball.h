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

class Ball
{
public:

	Vector2f position;

	CircleShape ball;

	float xVel = 200.f;

	float yVel = 200.f;

	Ball(float startx, float starty);

	Vector2f getPosition();

	CircleShape getball();

	bool ball_update(float dt, float paddlex, Sound& soundwallbounce);

	void resetBallPosition(Vector2f position);
};


