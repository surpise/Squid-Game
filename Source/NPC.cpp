#include "NPC.h"

NPC::NPC(float _y) :y(_y) {}

bool NPC::getDead()
{
	return dead;
}

void NPC::setDead()
{
	if (x <= 1185)
	{
		dead = true;
	}
}

void NPC::draw(RenderWindow& _window, SoundSource::Status s)
{
	Sprite body;
	Texture texture;

	if (s == SoundSource::Playing)
	{
		timer += 1;
	}

	if (dead == true)
	{
		texture.loadFromFile("images/npc6.png");
	}
	else if ((x >= 1200) || (x == 0))
	{
		texture.loadFromFile("images/npc1.png");
	}
	else
	{
		if (timer <= 15)
		{
			texture.loadFromFile("images/npc2.png");
		}
		else if (timer <= 30)
		{
			texture.loadFromFile("images/npc3.png");
		}
		else if (timer <= 45)
		{
			texture.loadFromFile("images/npc4.png");
		}
		else if (timer > 45)
		{
			timer = 0;
			texture.loadFromFile("images/npc5.png");
		}
	}
	body.setTexture(texture);
	body.setPosition(x, y);
	_window.draw(body);
}

void NPC::update(SoundSource::Status s, bool soonDead)
{
	if (dead == true || x >= 1200)
	{
		return;
	}

	random_device rng;
	uniform_int_distribution<int> dist(0, 3);
	int dir = dist(rng);
	if ((s == SoundSource::Playing) || (soonDead == true))
	{
		if (dir == 0)
		{
			if (y <= 0)
			{
				return;
			}
			y -= 1;
		}
		else if (dir == 1)
		{
			if (y >= 600)
			{
				return;
			}
			y += 1;
		}
		else
		{
			x += 1;
		}
	}

}