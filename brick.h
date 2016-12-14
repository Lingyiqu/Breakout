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

class Brick
{

public:
	RectangleShape brick;
	int hp;
	Vector2f position;

	void InitBrick(float posX,float posY);
	RectangleShape getbrick();
	FloatRect getPosition();
	void draw();
	void hit(); //{ --hp; }
	bool isDead(); //{ hp <= 0; }
	bool isCollision = false;
	bool Rightmove;
	bool shatter = false;
};
