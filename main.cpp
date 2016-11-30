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
#include "paddle.h"
#include "ball.h"
#include "brick.h"

using namespace std;

using namespace sf;

bool isPlay = true;

bool isBallMove = false;



RectangleShape  Back;

Texture background;

Texture bricktex;

Texture balltex;

SoundBuffer buf;

Sound sound;

RenderWindow window(VideoMode(window_width, window_height), "Breakout");

Ball myball(410, 563);

Paddle mypaddle(340, 580);

Brick mybrick[8][6];







bool paddle_overlap(FloatRect r, Vector2f p)
{
	return p.x >= r.left &&
		p.x < r.left + r.width &&
		p.y >= r.top &&
		p.y < r.top + r.height;

}

bool brick_overlap(FloatRect r, Vector2f p)
{
	return ((p.x >= r.left) &&
		(p.x < r.left + r.width) &&
		(p.y >= r.top) &&
		(p.y < r.top + r.height));	
}

//void create_bricks()
//{
//	for (int i = 0; i < 20; ++i)
//	{
//
//		Vector2f position =
//			//int hp = 1;
//			Brick* b = new Brick(posX, posY);
//		mybrick.push_back(unique_ptr<Brick>(b));
//	}
//}

int main()


{
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			mybrick[i][j].InitBrick(100 * i, 20*j);
		}
	}
	
	
	

	buf.loadFromFile("ball.wav");

	sound.setBuffer(buf);
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");

	Clock clock;
	//cout << "outMain\t";
	while (window.isOpen())//&& isPlay==true)
	{
		//cout << "inLOop\t";
		// check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::Black);

		background.loadFromFile("backy.jpg");

		Back.setSize(Vector2f(800, 600));

		Back.setPosition(0, 0);

		Back.setTexture(&background);

		//window.clear(Color(0, 0, 255));

		window.draw(Back);

		bricktex.loadFromFile("brick.png");
		
		balltex.loadFromFile("ball.png");

		myball.ball.setTexture(&balltex);
		
		balltex.setSmooth(true);

		float dt = clock.restart().asSeconds();

		window.draw(myball.getball());

		window.draw(mypaddle.getpaddle());
		
		for (int j = 0; j < 6; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (mybrick[i][j].isCollision == false)
				{

					window.draw(mybrick[i][j].getbrick());
					mybrick[i][j].brick.setTexture(&bricktex);
				}

			}
		}
		

		
		Text hud;

		Font font;

		font.loadFromFile("sansation.ttf");

		hud.setFont(font);

		hud.setCharacterSize(75);

		std::stringstream ss;

		ss << "\n\n\tScore:" << score << "\t\tLives:" << life;

		hud.setString(ss.str());

		window.draw(hud);

		

		

		if (myball.getPosition().y >= 600)

		{
			life--;
		}
		
		if (life <= 0)
		{
			myball.position.x = mypaddle.paddle.getPosition().x + 60 - 9;
			myball.ball.setPosition(myball.position);
			isBallMove == false; 
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			isBallMove = true;
		}
		
		if (isBallMove == true)
		{ 
			myball.ball_update(dt);
		}
		
		if (isBallMove == false)
		{
			myball.position.x =  mypaddle.paddle.getPosition().x+60-9;
			myball.ball.setPosition(myball.position);
		}

		mypaddle.paddle_update(dt);
		

		if (paddle_overlap(mypaddle.getPosition(), myball.getPosition()))
		{
			
			if (myball.getPosition().x <= 100)
			{
				myball.yVel = -myball.yVel;
				myball.xVel = myball.xVel;
			}
			if (myball.getPosition().x>100 && myball.getPosition().x<200)
			{
				myball.yVel = -myball.yVel;
				myball.xVel = myball.xVel;
			}

			if (myball.getPosition().x>=200 && myball.getPosition().x<=300)
			{
				myball.yVel = -myball.yVel;
				myball.xVel = myball.xVel;
			}

			if (myball.getPosition().x>300 && myball.getPosition().x<400)
			{
				myball.xVel = myball.xVel;
				myball.yVel = -myball.yVel;
			}

			if (myball.getPosition().x>= 400 && myball.getPosition().x<500)
			{
				myball.xVel = myball.xVel;
				myball.yVel = -myball.yVel;
			}

			if (myball.getPosition().x>= 500 && myball.getPosition().x<= 600)
			{
				myball.xVel = myball.xVel;
				myball.yVel = -myball.yVel;
			}

		}
		
		for (int j = 0; j < 6; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (paddle_overlap(mybrick[i][j].getPosition(), myball.getPosition()) && (mybrick[i][j].isCollision == false))
				{
					myball.yVel = -(1 + 0.005*(j-4))*myball.yVel;

					myball.xVel = (1 + 0.002*(j - 4))*myball.xVel;
					mybrick[i][j].isCollision = true;
					score++;
				}
			}
		}
		
		

		window.display();
	}
	return 0;

}
