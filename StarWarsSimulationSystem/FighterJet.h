#pragma once

#include "SpaceShip.h"
#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	namespace SpaceShips
	{
		class StarWarsObject FighterJet : public SpaceShip
		{
		public:
			FighterJet(int hp, int damage);
		};
	}
}

