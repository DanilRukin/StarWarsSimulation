#pragma once

#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	enum StarWarsObject DamageSender
	{
		CloneArmy, SpaceFleet
	};

	class StarWarsObject Damage
	{
	public:
		DamageSender Sender;
		int DamageAmount;
		Damage()
		{
			Sender = DamageSender::CloneArmy;
			DamageAmount = 0;
		}
	};
}
