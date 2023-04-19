#include "Player.h"

void Player::setDead()
{
	if (x <= 1185)
	{
		dead = true;
	}
}

bool Player::getDead()
{
	return dead;
}

float Player::getPos()
{
	return x;
}

void Player::moveUp()
{
	if (y <= 0.0f)
	{
		return;
	}
	y -= 1;
}

void Player::moveDown()
{
	if (y >= 600.0f)
	{
		return;
	}
	y += 1;
}

void Player::moveLeft()
{
	if (x <= 0.0f)
	{
		return;
	}
	x -= 1;
}

void Player::moveRight()
{
	if (x >= 1200.0f)
	{
		return;
	}
	x += 1.5f;
}

void Player::draw(RenderWindow& _window, SoundSource::Status s)
{
	Texture texture;

	if (s == SoundSource::Playing)
	{
		timer += 1;
	}

	if (dead == true)
	{
		texture.loadFromFile("images/player6.png");
	}
	else if ((x >= 1200) || (x == 0))
	{
		texture.loadFromFile("images/player1.png");
	}
	else
	{
		if (timer <= 15)
		{
			texture.loadFromFile("images/player2.png");
		}
		else if (timer <= 30)
		{
			texture.loadFromFile("images/player3.png");
		}
		else if (timer <= 45)
		{
			texture.loadFromFile("images/player4.png");
		}
		else if (timer <= 60)
		{
			texture.loadFromFile("images/player5.png");
		}
		else if (timer > 60)
		{
			texture.loadFromFile("images/player2.png");
			timer = 0;
		}
	}
	player.setTexture(texture);
	player.setPosition(x, y);
	_window.draw(player);
}