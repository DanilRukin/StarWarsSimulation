#pragma once

#include "GlabalNames.h"
#include "StarWarsAPI.h"
#include "PrintableObject.h"
#include "Queue.h"

namespace StarWarsSystem
{
	class StarWarsObject PlanetBlackMarket : public PrintableObject
	{
	private:
		const char* _planetBlackMarketTag = "[Планета 'Черный рынок']: ";
		Core::Queue<int>* _tanksSupplies; // поставки танков
		Core::Queue<int>* _spaceShipsSupplies; // поставки космических кораблей/средств ПВО
	public:
		PlanetBlackMarket(int tanksSuppliesCount, int spaceShipsSuppliesCount);
		~PlanetBlackMarket();
		/**
		* Продать (разместить) набор танков
		*/
		void PostTanksSupply(int count);
		/**
		* Продать (разместить) набор средств ПВО/космических кораблей
		*/
		void PostSpaceShipsSupply(int count);
		/**
		* Купить набор танков
		*/
		int BuyTanksSupply();
		/**
		* Купить набор средств ПВО/космических кораблей
		*/
		int BuySpaceShipSupply();
	};
}

