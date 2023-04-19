#include "NPC_Manager.h"

NPC_Manager::NPC_Manager()
{
	float _y = 55;
	for (int i = 1; i < 8; i++)
	{
		if (i == 4)
		{
			continue;
		}
		_y = 80.0f * i;

		NPC npc(_y);
		npcs.push_back(npc);
	}
}

bool NPC_Manager::getSoundplay()
{
	return sound_play;
}

void NPC_Manager::setSoundplay()
{
	sound_play = false;
}

void NPC_Manager::draw(RenderWindow& _window, SoundSource::Status s)
{
	for (auto& e : npcs)
	{
		e.draw(_window, s);
	}
}

void NPC_Manager::update(SoundSource::Status s, unsigned int deadNpc)
{
	bool soonDead = false;
	if (s == SoundSource::Stopped)
	{
		delay += 1;
		if ((delay == 30) && (deadNpc < npcs.size()))
		{
			if (npcs[deadNpc].getDead() == false)
			{
				npcs[deadNpc].setDead();
				if (npcs[deadNpc].getDead() == true)
				{
					sound_play = true;
				}
			}
		}
	}
	else
	{
		delay = 0;
	}

	for (unsigned int i = 0; i < npcs.size(); i++)
	{
		if (i == deadNpc)
		{
			soonDead = true;
		}
		else
		{
			soonDead = false;
		}
		npcs[i].update(s, soonDead);
	}
}