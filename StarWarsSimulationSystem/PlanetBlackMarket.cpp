#include "PlanetBlackMarket.h"

int StarWarsSystem::PlanetBlackMarket::BuySpaceShipSupply()
{
	Print(_planetBlackMarketTag, "Получен запрос на покупку набора средств ПВО/космических кораблей");
	EnterCriticalSection(&SpaceShipsBufferLock);
	while (_spaceShipsSupplies->Empty())
	{
		// пока буфер пуст, заставляем потребителя ждать
		SleepConditionVariableCS(&SpaceShipsBufferNotEmpty, &SpaceShipsBufferLock, INFINITE);
	}
	// продаем набор средств ПВО/космических кораблей
	int result = _spaceShipsSupplies->Dequeue();
	Print(_planetBlackMarketTag, "Набора танков продан");
	LeaveCriticalSection(&SpaceShipsBufferLock);
	// если производитель ожидает - разбудим его
	WakeConditionVariable(&SpaceShipsBufferNotFull);
	return result;
}

int StarWarsSystem::PlanetBlackMarket::BuyTanksSupply()
{
	Print(_planetBlackMarketTag, "Получен запрос на покупку набора танков");
	EnterCriticalSection(&TanksBufferLock);
	while (_tanksSupplies->Empty())
	{
		// пока буфер пуст, заставляем потребителя ждать
		SleepConditionVariableCS(&TanksBufferNotEmpty, &TanksBufferLock, INFINITE);
	}
	// продаем набор танков
	int result = _tanksSupplies->Dequeue();
	Print(_planetBlackMarketTag, "Набора танков продан");
	LeaveCriticalSection(&TanksBufferLock);
	// если производитель ожидает - разбудим его
	WakeConditionVariable(&TanksBufferNotFull);
	return result;
}

void StarWarsSystem::PlanetBlackMarket::PostSpaceShipsSupply(int count)
{
	Print(_planetBlackMarketTag, "Получен запрос на размещение новового набора ПВО/космических вооружений");
	EnterCriticalSection(&SpaceShipsBufferLock);
	while (_spaceShipsSupplies->Full())
	{
		// усыпляем производителя, пока не освободится место на черном рынке
		SleepConditionVariableCS(&SpaceShipsBufferNotFull, &SpaceShipsBufferLock, INFINITE);
	}
	// разместим набор средств ПВО/космических вооружений на черном рынке
	_spaceShipsSupplies->Enqueue(count);
	Print(_planetBlackMarketTag, "Набор ПВО/космических вооружений размещен");
	LeaveCriticalSection(&SpaceShipsBufferLock);
	// если потребитель ожидает, то разбудим его.
	WakeConditionVariable(&SpaceShipsBufferNotEmpty);
}

void StarWarsSystem::PlanetBlackMarket::PostTanksSupply(int count)
{
	Print(_planetBlackMarketTag, "Получен запрос на размещение новового набора танков");
	EnterCriticalSection(&TanksBufferLock);
	while (_tanksSupplies->Full())
	{
		// усыпляем производителя, пока не освободится место на черном рынке
		SleepConditionVariableCS(&TanksBufferNotFull, &TanksBufferLock, INFINITE);
	}
	// разместим набор танков на черном рынке
	_tanksSupplies->Enqueue(count);
	Print(_planetBlackMarketTag, "Набор танков размещен");
	LeaveCriticalSection(&TanksBufferLock);
	// если потребитель ожидает, то разбудим его.
	WakeConditionVariable(&TanksBufferNotEmpty);
}

StarWarsSystem::PlanetBlackMarket::PlanetBlackMarket(int tanksSuppliesCount, int spaceShipsSuppliesCount) : PrintableObject(true)
{
	_tanksSupplies = new Core::Queue<int>(tanksSuppliesCount);
	_spaceShipsSupplies = new Core::Queue<int>(spaceShipsSuppliesCount);
}

StarWarsSystem::PlanetBlackMarket::~PlanetBlackMarket()
{
	if (_tanksSupplies != nullptr)
	{
		delete _tanksSupplies;
		_tanksSupplies = nullptr;
	}
	if (_spaceShipsSupplies != nullptr)
	{
		delete _spaceShipsSupplies;
		_spaceShipsSupplies = nullptr;
	}
}
