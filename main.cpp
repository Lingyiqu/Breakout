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

Texture crackedbrick;

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

	buf.loadFromFile("ball.wav");

	sound.setBuffer(buf);
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");

	Clock clock;
	//cout << "outMain\t";

	bricktex.loadFromFile("brick.png");

	crackedbrick.loadFromFile("crackedbrick.png");

	balltex.loadFromFile("ball.png");

	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			mybrick[i][j].InitBrick(100 * i, 20 * j);
			mybrick[i][j].brick.setTexture(&bricktex);
		}
	}

	for (int i = 0; i < 8; i++)    
	{
		mybrick[i][5].hp = 2;
	}


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

		float dt = clock.restart().asSeconds();

		window.clear(Color::Black);

		//background.loadFromFile("backy.jpg");

		Back.setSize(Vector2f(800, 600));

		Back.setPosition(0, 0);

		//Back.setTexture(&background);

		//window.clear(Color(0, 0, 255));

		window.draw(Back);

		

		myball.ball.setTexture(&balltex);
		
		balltex.setSmooth(true);

		

		window.draw(myball.getball());

		window.draw(mypaddle.getpaddle());
		
		for (int j = 0; j < 6; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (mybrick[i][j].isCollision == false)
				{
					window.draw(mybrick[i][j].getbrick());					
					

				}

			}
		}
		


		
		Text hud;

		Font font;

		font.loadFromFile("sansation.ttf");

		hud.setFont(font);

		hud.setCharacterSize(75);

		hud.setColor(Color::Blue);

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
		

		if (paddle_overlap(mypaddle.getPosition(), myball.getPosition())&&( myball.yVel>0))
		{
			
			myball.yVel = -myball.yVel;
			
			myball.xVel = myball.xVel;
		}
		
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				mybrick[i][j].hp = 1;
				if (paddle_overlap(mybrick[i][j].getPosition(), myball.getPosition()) && (mybrick[i][j].isCollision == false))
				{
					mybrick[i][j].hp--;

					myball.yVel = -(1 + 0.005*(j-4))*myball.yVel;

					myball.xVel = (1 + 0.002*(j - 4))*myball.xVel;
					
					if (mybrick[i][j].hp <= 0)
					{
						mybrick[i][j].isCollision = true;
						score++;
					}
					
					}

				
				
				
			}
		}
		
		for (int i = 0; i < 8; i++)
		{
			//mybrick[i][5].hp =2;
			if (paddle_overlap(mybrick[i][5].getPosition(), myball.getPosition()) && (mybrick[i][5].isCollision == false))
			{
				cout << "\thp0: " << mybrick[i][5].hp;

				

				mybrick[i][5].hp--;

				myball.yVel = -(1 + 0.005*(5 - 4))*myball.yVel;

				myball.xVel = (1 + 0.002*(5 - 4))*myball.xVel;
				cout << "\thp1: " << mybrick[i][5].hp;
				if (mybrick[i][5].hp <= 0)
				{
					cout << "\thp2: " << mybrick[i][5].hp;
					mybrick[i][5].isCollision = true;
					score++;
				}

			}
			if (mybrick[i][5].hp == 1)
			{
				cout << "\thp3: " << mybrick[i][5].hp;

			//crackedbrick.loadFromFile("crackedbrick.png");
			mybrick[i][5].brick.setTexture(&crackedbrick);
			}
			
		}
		
		

		window.display();
	}
	return 0;

}
