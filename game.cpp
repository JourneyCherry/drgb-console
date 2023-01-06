#include "game.hpp"

game::game()
{
	actions.fill(action_type::meditate);
	healths.fill(MAX_HEALTH);
	energies.fill(0);
	required_energy[action_type::meditate]	 = 0;
	required_energy[action_type::guard]		 = 0;
	required_energy[action_type::punch]		 = 1;
	required_energy[action_type::evade]		 = 1;
	required_energy[action_type::fire]		 = 2;
}

bool game::input(int player, int action)
{
	if(player < 0 || player >= MAX_PLAYER)
		return false;
	if(action < 0 || action >= action_type::count)	//TODO : ACTION_COUNT로 변경 필요
		return false;

	action_type target = (action_type)(1 << action);
	if(energies[player] < required_energy[target])
		return false;
	actions[player] = target;
	return true;
}

bool game::process()
{
	for(int i = 0;i<MAX_PLAYER;i++)
	{
		switch(actions[i])
		{
			case action_type::meditate:
				energies[i] = std::min(MAX_ENERGY, energies[i]+1);
				break;
			case action_type::punch:
				{
					int target = opponent(i);
					if(actions[target] & 0x01)	//meditate
						healths[target] -= 1;
				}
				break;
			case action_type::fire:
				{
					int target = opponent(i);
					if(actions[target] & 0x07)	//meditate, guard, punch
						healths[target] -= 1;
				}
				break;
		}
		energies[i] -= required_energy[actions[i]];
	}

	for(int i = 0;i<MAX_PLAYER;i++)
	{
		if(healths[i] <= 0)
			return true;
		actions[i] = action_type::meditate;
	}
	return false;
}

int game::getwinner()
{
	int alived = -1;
	for(int i = 0;i<MAX_PLAYER;i++)
	{
		if(healths[i] > 0)
		{
			if(alived >= 0)
				return -1;
			alived = i;
		}
	}
	return alived;
}

int game::opponent(const int& player)
{
	return (player+1)%MAX_PLAYER;
}