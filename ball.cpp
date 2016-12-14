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
#include "ball.h"

using namespace std;

using namespace sf;


Ball::Ball(float startx, float starty)
{

	position.x = startx;

	position.y = starty;

	ball.setRadius(15);

	ball.setOrigin(15, 15);

	ball.setFillColor(sf::Color(127,255,212));

	ball.getPosition();

	ball.setPosition(position);
}

CircleShape Ball::getball()
{
	return ball;
}

bool Ball::ball_update(float dt,float paddlex,Sound& soundwallbounce)

{
	Vector2f pos = ball.getPosition();

	pos.y += yVel * dt;

	pos.x += xVel * dt;


	if ((pos.y > window_height) && (yVel > 0))
	{
		//pos.y = 20;
		//pos.x = paddlex+ 60;
		yVel = 0;
		xVel = 0;
		return true;
	}

	if ((pos.y < 0) && (yVel < 0))
	{
		yVel = -yVel;
		if (soundwallbounce.getStatus() != SoundSource::Playing) soundwallbounce.play();
	}
		

	if ((pos.x > window_width) && (xVel> 0))
	{
		if (soundwallbounce.getStatus() != SoundSource::Playing) soundwallbounce.play();
		xVel = -xVel;
	}
		

	if ((pos.x < 0) &&(xVel < 0))
	{
		if (soundwallbounce.getStatus() != SoundSource::Playing) soundwallbounce.play();
		xVel = -xVel;
	}

	ball.setPosition(pos);
	return false;
}

void Ball::resetBallPosition(Vector2f position)
{
	ball.setPosition(position);
}


Vector2f Ball::getPosition()
{
	return ball.getPosition();
}

