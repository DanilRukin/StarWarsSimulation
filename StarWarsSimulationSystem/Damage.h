#pragma once

#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	enum StarWarsObject DamageSender
	{
		ArmyOfClones, Fleet
	};

	class StarWarsObject Damage
	{
	public:
		DamageSender Sender;
		int DamageAmount;
		Damage()
		{
			Sender = DamageSender::ArmyOfClones;
			DamageAmount = 0;
		}
	};
}
