#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Player
{
private:
	Sprite player;
	bool dead = false;
	int timer = 0;
	float x = 0.0f;
	float y = 320.0f;
public:
	void setDead();
	bool getDead();
	float getPos();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void draw(RenderWindow& _window, SoundSource::Status s);
};