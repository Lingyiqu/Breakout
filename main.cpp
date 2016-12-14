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

SoundBuffer bufshatter;
Sound soundshatter;




SoundBuffer bufbreak;
Sound soundbreak;


SoundBuffer bufballlost;
Sound soundballlost;

SoundBuffer bufpaddlebounce;
Sound soundpaddlebounce;

SoundBuffer bufgameover;
Sound soundgameover;

SoundBuffer buflevelcomplete;
Sound soundlevelcomplete;

SoundBuffer bufwallbounce;
Sound soundwallbounce;


RenderWindow window(VideoMode(window_width, window_height), "Breakout");

Ball myball(410, 563);

Paddle mypaddle(340, 580);

Brick mybrick[8][3];

Brick powerfulbrick;

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

int main()
{
	bufshatter.loadFromFile("shatter.wav");
	soundshatter.setBuffer(bufshatter);
	bufbreak.loadFromFile("break.wav");
	soundbreak.setBuffer(bufbreak);
	bufballlost.loadFromFile("balllost.wav");
	soundballlost.setBuffer(bufballlost);
	bufpaddlebounce.loadFromFile("paddlebounce.wav");
	soundpaddlebounce.setBuffer(bufpaddlebounce);
	bufgameover.loadFromFile("gameover.wav");
	soundgameover.setBuffer(bufgameover);
	buflevelcomplete.loadFromFile("levelcomplete.wav");
	soundlevelcomplete.setBuffer(buflevelcomplete);
	bufwallbounce.loadFromFile("wallbounce.wav");
	soundwallbounce.setBuffer(bufwallbounce);


	powerfulbrick.InitBrick(400, 100);
	powerfulbrick.brick.setTexture(&bricktex);
	powerfulbrick.brick.setFillColor(Color::Cyan);
	powerfulbrick.Rightmove = true;

	int level = 1;


	Clock clock;

	bricktex.loadFromFile("brick.png");

	crackedbrick.loadFromFile("crackedbrick.png");

	balltex.loadFromFile("ball.png");

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			mybrick[i][j].InitBrick(100 * i, 20 * j);
			mybrick[i][j].brick.setTexture(&bricktex);
			if (level == 1)
			{
				if ((j == 0) || (j == 1))
				{
					mybrick[i][j].hp = 1;
				}
				if(j == 2)
				{
					mybrick[i][j].brick.setFillColor(Color::Yellow);
					mybrick[i][j].hp = 2;
				}
			}
			if (level == 2)
			{
				if ((j==1)||(j == 2))
				{
					mybrick[i][j].brick.setFillColor(Color::Yellow);
					mybrick[i][j].hp = 2;
				}
				if (j == 0)
				{
					mybrick[i][j].hp = 1;
				}
			}
		}
	}


	while (window.isOpen())
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

		Back.setSize(Vector2f(800, 600));

		Back.setPosition(0, 0);

		window.draw(Back);

		myball.ball.setTexture(&balltex);

		balltex.setSmooth(true);

		window.draw(myball.getball());

		window.draw(mypaddle.getpaddle());

		for (int j = 0; j < 3; j++)
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

		//Powerfulbrick part
		if( (powerfulbrick.Rightmove == true)&&(powerfulbrick.brick.getPosition().x<=window_width-120))
		{
			powerfulbrick.brick.setPosition(powerfulbrick.brick.getPosition().x + 2, powerfulbrick.brick.getPosition().y);
		}
		if ((powerfulbrick.Rightmove == true) && (powerfulbrick.brick.getPosition().x > window_width - 120))
		{
			powerfulbrick.Rightmove = false;
		}
		if ((powerfulbrick.Rightmove == false) && (powerfulbrick.brick.getPosition().x >=0))
		{
			powerfulbrick.brick.setPosition(powerfulbrick.brick.getPosition().x - 2, powerfulbrick.brick.getPosition().y);
		}
		if ((powerfulbrick.Rightmove == false) && (powerfulbrick.brick.getPosition().x <0))
		{
			powerfulbrick.Rightmove = true;
		}

		if (paddle_overlap(powerfulbrick.getPosition(), myball.getPosition()))
		{
			myball.yVel = -(1 + 0.005 * 3)*myball.yVel;

			myball.xVel = (1 + 0.002 * 3)*myball.xVel;
			if (soundpaddlebounce.getStatus() != SoundSource::Playing) soundpaddlebounce.play();
		}
		window.draw(powerfulbrick.brick);


		/*if (myball.getPosition().y >= 600)

		{
			life--;
		}*/

		if (life <= 0)
		{
			myball.position.x = mypaddle.paddle.getPosition().x + 60 - 9;
			myball.ball.setPosition(myball.position);
			isBallMove == false;
			if (soundgameover.getStatus() != SoundSource::Playing) soundgameover.play();
		}

		if((isBallMove==false)&& (Keyboard::isKeyPressed(Keyboard::Space)))
		{
			isBallMove = true;
			myball.xVel = 200.f;
			myball.yVel = 200.f;
		}

		if (isBallMove == true)
		{
			if (myball.ball_update(dt, mypaddle.paddle.getPosition().x,soundwallbounce))
			{
				life--;
				isBallMove = false;
				if (soundballlost.getStatus() != SoundSource::Playing) soundballlost.play();
			}
		}

		if (isBallMove == false)
		{
			myball.position.x = mypaddle.paddle.getPosition().x + 60 - 9;
			myball.ball.setPosition(myball.position);
		}

		mypaddle.paddle_update(dt);


		if (paddle_overlap(mypaddle.getPosition(), myball.getPosition()) && (myball.yVel > 0))
		{

			myball.yVel = -myball.yVel;

			myball.xVel = myball.xVel;
		}

		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (paddle_overlap(mybrick[i][j].getPosition(), myball.getPosition()) && (mybrick[i][j].isCollision == false))
				{
					mybrick[i][j].hp--;
					
					score++;

					myball.yVel = -(1 + 0.005*(j - 1))*myball.yVel;

					myball.xVel = (1 + 0.002*(j - 1))*myball.xVel;

					if (mybrick[i][j].hp <= 0)
					{
						mybrick[i][j].isCollision = true;
						if (soundbreak.getStatus() != SoundSource::Playing) soundbreak.play();
						
					}
				}
			}
		}

		/*for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if ((level == 1) && (j == 2))
				{
					if (paddle_overlap(mybrick[i][j].getPosition(), myball.getPosition()) && (mybrick[i][j].isCollision == false))
					{
						//cout << "\thp0: " << mybrick[i][j].hp;

						mybrick[i][j].hp--;

						//myball.yVel = -(1 + 0.005*(5 - 4))*myball.yVel;

						//myball.xVel = (1 + 0.002*(5 - 4))*myball.xVel;
						//cout << "\thp1: " << mybrick[i][j].hp;
						if (mybrick[i][j].hp <= 0)
						{
							//cout << "\thp2: " << mybrick[i][j].hp;
							mybrick[i][j].isCollision = true;
							score += 2;
						}

					}
					if (mybrick[i][j].hp == 1)
					{
						//cout << "\thp3: " << mybrick[i][j].hp;

						//crackedbrick.loadFromFile("crackedbrick.png");
						mybrick[i][j].brick.setTexture(&crackedbrick);
					}
				}
				if ((level == 2) && ((j==1)||(j == 2)))
				{
					if (paddle_overlap(mybrick[i][j].getPosition(), myball.getPosition()) && (mybrick[i][j].isCollision == false))
					{
						//cout << "\thp0: " << mybrick[i][j].hp;

						mybrick[i][j].hp--;

						//myball.yVel = -(1 + 0.005*(5 - 4))*myball.yVel;

						//myball.xVel = (1 + 0.002*(5 - 4))*myball.xVel;
						//cout << "\thp1: " << mybrick[i][j].hp;
						if (mybrick[i][j].hp <= 0)
						{
							//cout << "\thp2: " << mybrick[i][j].hp;
							mybrick[i][j].isCollision = true;
							score += 2;
						}

					}
					if (mybrick[i][j].hp == 1)
					{
					//	cout << "\thp3: " << mybrick[i][j].hp;

						//crackedbrick.loadFromFile("crackedbrick.png");
						mybrick[i][j].brick.setTexture(&crackedbrick);
					}
				}
			}
		}*/
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (((level == 1) && (j == 2)) || ((level == 2) && ((j == 1) || (j == 2))))
				{
					if (mybrick[i][j].hp == 1)
					{
						mybrick[i][j].brick.setTexture(&crackedbrick);
						if (mybrick[i][j].shatter == false)
						{
							if (soundshatter.getStatus() != SoundSource::Playing) soundshatter.play();
							mybrick[i][j].shatter = true;
						}
						
					}
				}
			}
		}

		if ((level==1)&&(score == 32))
		{
			level = 2;
			score = 0;
			if (soundlevelcomplete.getStatus() != SoundSource::Playing) soundlevelcomplete.play();
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					mybrick[i][j].InitBrick(100 * i, 20 * j);
					mybrick[i][j].isCollision == false;
					mybrick[i][j].brick.setTexture(&bricktex);
					if (j == 0)
					{
						mybrick[i][j].hp = 1;
					}
					if ((j == 1) || (j == 2))
					{
						mybrick[i][j].brick.setFillColor(Color::Yellow);
						mybrick[i][j].hp = 2;
					}
				}
			}
		}
		if ((level == 2) && (score == 40))
		{
			level = 1;
			score = 0;
			if (soundlevelcomplete.getStatus() != SoundSource::Playing) soundlevelcomplete.play();
			myball.xVel *= 1.25;
			myball.yVel *= 1.25;
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					mybrick[i][j].InitBrick(100 * i, 20 * j);
					mybrick[i][j].brick.setTexture(&bricktex);
					mybrick[i][j].isCollision == false;
					if ((j == 0) || (j = 1))
					{
						mybrick[i][j].hp = 1;
					}
					if (j==2)
					{
						mybrick[i][j].brick.setFillColor(Color::Yellow);
						mybrick[i][j].hp = 2;
					}
				}
			}
		}

		window.display();
	}
	return 0;

}
