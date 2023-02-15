#pragma once

#include "StarWarsAPI.h"
#include "PrintableObject.h"
#include "PlanetBlackMarket.h"
#include "Random.h"
#include "ReadWriteLockObject.h"

namespace StarWarsSystem
{
	class StarWarsObject SpaceShipsComapny : public ReadWriteLockObject
	{
	private:
		PlanetBlackMarket* _blackMarket;
		int _id;
		Core::Random _random;
		const int MAX_SHIPS_COUNT = 100;
	public:
		SpaceShipsComapny(int id, PlanetBlackMarket* blackMarket);

		void Run();
	};
}

