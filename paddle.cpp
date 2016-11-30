

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
#include "paddle.h"
#include "global.h"

using namespace std;

using namespace sf;


FloatRect Paddle::getPosition()

{
	FloatRect bat{ paddle.getPosition().x,paddle.getPosition().y,120,20 };
	return bat;
}


Paddle::Paddle(float startx, float starty)
{
	position.x = startx;

	position.y = starty;

	paddle.setSize(Vector2f(120, 20));

	paddle.setPosition(position);

	paddle.setFillColor(sf::Color(255, 192,203));
}

RectangleShape Paddle::getpaddle()
{
	return paddle;
}


void Paddle::paddle_update(float dt)

{

	Vector2f pos = paddle.getPosition();

	if (pos.x <= 0)

	{
		if (Keyboard::isKeyPressed(Keyboard::Right))

			pos.x += 400 * dt;
		paddle.setPosition(pos);

	}
	else if (pos.x < window_width - 120)

	{
		if (Keyboard::isKeyPressed(Keyboard::Left))

			pos.x -= 400 * dt;


		if (Keyboard::isKeyPressed(Keyboard::Right))

			pos.x += 400 * dt;

		paddle.setPosition(pos);

	}
	else if (pos.x >= window_width - 120)

	{
		if (Keyboard::isKeyPressed(Keyboard::Left))

			pos.x -= 400 * dt;

		paddle.setPosition(pos);

	}



	/*else

	pos.y += 0;*/
	//paddle.setPosition(pos);

}


