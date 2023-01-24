#pragma once

#include "SpaceShip.h"

namespace StarWarsSystem
{
	namespace SpaceShips
	{
		class Flagship : public SpaceShip
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

