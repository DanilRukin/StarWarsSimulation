#include "PlanetBlackMarketRWL.h"


StarWarsSystem::PlanetBlackMarketRWL::PlanetBlackMarketRWL(int tanksSuppliesCount, int spaceShipsSuppliesCount) : PlanetBlackMarket(tanksSuppliesCount, spaceShipsSuppliesCount)
{

}

void StarWarsSystem::PlanetBlackMarketRWL::PostTanksSupply(int count)
{
	Print(_planetBlackMarketTag, "Получен запрос на размещение нового набора танков");
	// разместим набор танков на черном рынке
	_tanksSupplies->Enqueue(count);
	Print(_planetBlackMarketTag, "Набор танков размещен");
}

void StarWarsSystem::PlanetBlackMarketRWL::PostSpaceShipsSupply(int count)
{
	Print(_planetBlackMarketTag, "Получен запрос на размещение нового набора ПВО/космических вооружений");
	// разместим набор средств ПВО/космических вооружений на черном рынке
	_spaceShipsSupplies->Enqueue(count);
	Print(_planetBlackMarketTag, "Набор ПВО/космических вооружений размещен");
}

int StarWarsSystem::PlanetBlackMarketRWL::BuySpaceShipSupply()
{
	Print(_planetBlackMarketTag, "Получен запрос на покупку набора средств ПВО/космических кораблей");
	// продаем набор средств ПВО/космических кораблей
	int result = _spaceShipsSupplies->Dequeue();
	Print(_planetBlackMarketTag, "Набора танков продан");
	return result;
}

int StarWarsSystem::PlanetBlackMarketRWL::BuyTanksSupply()
{
	Print(_planetBlackMarketTag, "Получен запрос на покупку набора танков");
	// продаем набор танков
	int result = _tanksSupplies->Dequeue();
	Print(_planetBlackMarketTag, "Набора танков продан");
	return result;
}
