#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

using namespace std;
using namespace sf;

class NPC
{
	float x = 0;
	float y;
	bool dead = false;
	int timer = 0;
public:
	NPC(float _y);
	bool getDead();
	void setDead();
	void draw(RenderWindow& _window, SoundSource::Status s);
	void update(SoundSource::Status s, bool soonDead);
};