#pragma once

#include "FighterJet.h"
#include "Flagship.h"
#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	namespace SpaceShips
	{
		class StarWarsObject SpaceShipsFactory
		{
		public:
			FighterJet* CreateFighterJet()
			{
				FighterJet* fighterJet = new FighterJet(100, 350);
				return fighterJet;
			}

			Flagship* CreateFlagship()
			{
				Flagship* flagShip = new Flagship(10000, 50000, 1000);
				return flagShip;
			}
		};
	}
}

