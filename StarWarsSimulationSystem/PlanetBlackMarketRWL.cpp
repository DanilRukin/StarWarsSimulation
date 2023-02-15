#include "PlanetBlackMarketRWL.h"


StarWarsSystem::PlanetBlackMarketRWL::PlanetBlackMarketRWL(int tanksSuppliesCount, int spaceShipsSuppliesCount) : PlanetBlackMarket(tanksSuppliesCount, spaceShipsSuppliesCount)
{

}

void StarWarsSystem::PlanetBlackMarketRWL::PostTanksSupply(int count)
{
	Print(_planetBlackMarketTag, "������� ������ �� ���������� ������ ������ ������");
	// ��������� ����� ������ �� ������ �����
	_tanksSupplies->Enqueue(count);
	Print(_planetBlackMarketTag, "����� ������ ��������");
}

void StarWarsSystem::PlanetBlackMarketRWL::PostSpaceShipsSupply(int count)
{
	Print(_planetBlackMarketTag, "������� ������ �� ���������� ������ ������ ���/����������� ����������");
	// ��������� ����� ������� ���/����������� ���������� �� ������ �����
	_spaceShipsSupplies->Enqueue(count);
	Print(_planetBlackMarketTag, "����� ���/����������� ���������� ��������");
}

int StarWarsSystem::PlanetBlackMarketRWL::BuySpaceShipSupply()
{
	Print(_planetBlackMarketTag, "������� ������ �� ������� ������ ������� ���/����������� ��������");
	// ������� ����� ������� ���/����������� ��������
	int result = _spaceShipsSupplies->Dequeue();
	Print(_planetBlackMarketTag, "������ ������ ������");
	return result;
}

int StarWarsSystem::PlanetBlackMarketRWL::BuyTanksSupply()
{
	Print(_planetBlackMarketTag, "������� ������ �� ������� ������ ������");
	// ������� ����� ������
	int result = _tanksSupplies->Dequeue();
	Print(_planetBlackMarketTag, "������ ������ ������");
	return result;
}
