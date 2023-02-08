#pragma once

#include "StarWarsAPI.h"
#include "PrintableObject.h"
#include "PlanetBlackMarket.h"
#include "Random.h"

namespace StarWarsSystem
{
	class StarWarsObject SpaceShipsComapny : public PrintableObject
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

