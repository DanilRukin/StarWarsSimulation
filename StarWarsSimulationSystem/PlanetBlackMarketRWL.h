#pragma once 

#include "PlanetBlackMarket.h"
#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	class StarWarsObject PlanetBlackMarketRWL : public PlanetBlackMarket
	{
	public:
		PlanetBlackMarketRWL(int tanksSuppliesCount, int spaceShipsSuppliesCount);
		/**
		* Продать (разместить) набор танков
		*/
		void PostTanksSupply(int count) override;
		/**
		* Продать (разместить) набор средств ПВО/космических кораблей
		*/
		void PostSpaceShipsSupply(int count) override;
		/**
		* Купить набор танков
		*/
		int BuyTanksSupply() override;
		/**
		* Купить набор средств ПВО/космических кораблей
		*/
		int BuySpaceShipSupply() override;
	};
}
