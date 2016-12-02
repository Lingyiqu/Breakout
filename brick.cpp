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
#include "brick.h"

using namespace std;

using namespace sf;

vector<unique_ptr<Brick>> bricks;



void Brick::InitBrick(float posX, float posY)
{
	position.x = posX;
	position.y = posY;
	brick.setSize(Vector2f(100, 20));
	brick.setPosition(position);
	brick.setFillColor(sf::Color(250,255, 255));
}

RectangleShape Brick::getbrick()
{
	return brick;
}

FloatRect Brick::getPosition()

{
	FloatRect bat{ brick.getPosition().x,brick.getPosition().y,100,20 };
	return bat;
}


