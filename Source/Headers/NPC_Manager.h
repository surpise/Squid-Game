#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "NPC.h"

using namespace std;
using namespace sf;

class NPC_Manager
{
	vector<NPC>npcs;
	int delay = 0;
	bool sound_play = false;
public:
	NPC_Manager();
	bool getSoundplay();
	void setSoundplay();
	void draw(RenderWindow& _window, SoundSource::Status s);
	void update(SoundSource::Status s, unsigned int deadNpc);
};