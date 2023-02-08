#include "PlanetBlackMarket.h"

int StarWarsSystem::PlanetBlackMarket::BuySpaceShipSupply()
{
	Print(_planetBlackMarketTag, "������� ������ �� ������� ������ ������� ���/����������� ��������");
	EnterCriticalSection(&SpaceShipsBufferLock);
	while (_spaceShipsSupplies->Empty())
	{
		// ���� ����� ����, ���������� ����������� �����
		SleepConditionVariableCS(&SpaceShipsBufferNotEmpty, &SpaceShipsBufferLock, INFINITE);
	}
	// ������� ����� ������� ���/����������� ��������
	int result = _spaceShipsSupplies->Dequeue();
	Print(_planetBlackMarketTag, "������ ������ ������");
	LeaveCriticalSection(&SpaceShipsBufferLock);
	// ���� ������������� ������� - �������� ���
	WakeConditionVariable(&SpaceShipsBufferNotFull);
	return result;
}

int StarWarsSystem::PlanetBlackMarket::BuyTanksSupply()
{
	Print(_planetBlackMarketTag, "������� ������ �� ������� ������ ������");
	EnterCriticalSection(&TanksBufferLock);
	while (_tanksSupplies->Empty())
	{
		// ���� ����� ����, ���������� ����������� �����
		SleepConditionVariableCS(&TanksBufferNotEmpty, &TanksBufferLock, INFINITE);
	}
	// ������� ����� ������
	int result = _tanksSupplies->Dequeue();
	Print(_planetBlackMarketTag, "������ ������ ������");
	LeaveCriticalSection(&TanksBufferLock);
	// ���� ������������� ������� - �������� ���
	WakeConditionVariable(&TanksBufferNotFull);
	return result;
}

void StarWarsSystem::PlanetBlackMarket::PostSpaceShipsSupply(int count)
{
	Print(_planetBlackMarketTag, "������� ������ �� ���������� �������� ������ ���/����������� ����������");
	EnterCriticalSection(&SpaceShipsBufferLock);
	while (_spaceShipsSupplies->Full())
	{
		// �������� �������������, ���� �� ����������� ����� �� ������ �����
		SleepConditionVariableCS(&SpaceShipsBufferNotFull, &SpaceShipsBufferLock, INFINITE);
	}
	// ��������� ����� ������� ���/����������� ���������� �� ������ �����
	_spaceShipsSupplies->Enqueue(count);
	Print(_planetBlackMarketTag, "����� ���/����������� ���������� ��������");
	LeaveCriticalSection(&SpaceShipsBufferLock);
	// ���� ����������� �������, �� �������� ���.
	WakeConditionVariable(&SpaceShipsBufferNotEmpty);
}

void StarWarsSystem::PlanetBlackMarket::PostTanksSupply(int count)
{
	Print(_planetBlackMarketTag, "������� ������ �� ���������� �������� ������ ������");
	EnterCriticalSection(&TanksBufferLock);
	while (_tanksSupplies->Full())
	{
		// �������� �������������, ���� �� ����������� ����� �� ������ �����
		SleepConditionVariableCS(&TanksBufferNotFull, &TanksBufferLock, INFINITE);
	}
	// ��������� ����� ������ �� ������ �����
	_tanksSupplies->Enqueue(count);
	Print(_planetBlackMarketTag, "����� ������ ��������");
	LeaveCriticalSection(&TanksBufferLock);
	// ���� ����������� �������, �� �������� ���.
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
