#pragma once

#include "SpaceShip.h"
#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	namespace SpaceShips
	{
		class StarWarsObject Flagship : public SpaceShip
		{
		private:
			int _energyShieldHealthPoints;
		public:
			Flagship(int hp, int damage, int energyShieldHealthPoints);

			void AcceptDamage(int damage) override;

			int DoDamage() override;
		};
	}
}

