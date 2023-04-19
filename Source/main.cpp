#include "Player.h"
#include "NPC.h"
#include "NPC_Manager.h"

int main()
{
	RenderWindow window(VideoMode(1280, 720), "Game");
	window.setFramerateLimit(60);

	Text text;
	Font font;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setPosition(560.0f, 360.0f);
	text.setCharacterSize(35);

	Texture bg;
	bg.loadFromFile("images/playground.png");
	Sprite background;
	background.setTexture(bg);
	background.setPosition(0.1f, 0.1f);

	int sound_period = 0;
	SoundBuffer buffer1;
	buffer1.loadFromFile("sound/doll.wav");
	Sound sound;
	sound.setBuffer(buffer1);

	SoundBuffer buffer2;
	buffer2.loadFromFile("sound/shot.wav");
	Sound shot;
	shot.setBuffer(buffer2);

	Text text2;
	Font font2;
	font2.loadFromFile("arial.ttf");
	text2.setFont(font);
	text2.setFillColor(Color::Red);
	text2.setPosition(25.0f, 15.0f);
	text2.setCharacterSize(60);
	int limit_time = 60;
	int timecheck = 0;

	Player player;
	NPC_Manager npcs;
	int deadNpc = -1;
	int timer = 0;
	bool gameover = false;


	while (window.isOpen())
	{
		Event event;

		timecheck += 1;
		if (timecheck == 60)
		{
			limit_time -= 1;
			timecheck = 0;
		}

		if(sound.getStatus() == SoundSource::Stopped)
		{
			sound_period += 1;
		}	

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (sound.getStatus() == SoundSource::Stopped)
				{
					if (gameover == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Enter) == true)
						{
							window.close();
						}
					}
					else
					{
						player.setDead();
						shot.play();
					}
				}
				else if(player.getDead() == false)
				{
					if (Keyboard::isKeyPressed(Keyboard::Up) == true)
					{
						player.moveUp();
					}
					else if (Keyboard::isKeyPressed(Keyboard::Down) == true)
					{
						player.moveDown();
					}
					else if (Keyboard::isKeyPressed(Keyboard::Left) == true)
					{
						player.moveLeft();
					}
					else if (Keyboard::isKeyPressed(Keyboard::Right) == true)
					{
						player.moveRight();
					}
				}
			default:
				break;
			}	
		}

		if ((sound_period) > 120 && (gameover == false))
		{
			sound.play();
			sound_period = 0;
			random_device rng;
			uniform_int_distribution<int> dist(0, 5);
			deadNpc = dist(rng);
		}

		if (limit_time == 0)
		{
			sound.stop();
			player.setDead();
			if (player.getDead() == true)
			{
				shot.play();
			}
			limit_time = -1;
		}

		npcs.update(sound.getStatus(), deadNpc);
		
		if (npcs.getSoundplay() == true)
		{
			shot.play();
			if (gameover != true)
			{
				npcs.setSoundplay();
			}
		}

		window.clear();

		if (limit_time <= 0)
		{
			text2.setString(to_string(0));
		}
		else
		{
			text2.setString(to_string(limit_time));
		}

		window.draw(background);
		window.draw(text2);
		npcs.draw(window, sound.getStatus());
		player.draw(window,sound.getStatus());

		if (player.getDead() == true)
		{
			timer += 1;
			if (timer > 60)
			{
				sound.stop();
				window.clear();
				text.setString("Game over");
				window.draw(text);
				gameover = true;
			}
		}

		if (player.getPos() >= 1200)
		{
			timer += 1;
			if (timer > 60)
			{
				window.clear();
				text.setString("You Win!");
				window.draw(text);
				gameover = true;
				npcs.setSoundplay();
				sound.stop();
			}
		}

		window.display();
	}
	return 0;
}