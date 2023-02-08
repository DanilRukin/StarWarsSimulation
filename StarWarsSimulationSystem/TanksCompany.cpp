#include "TanksCompany.h"

StarWarsSystem::TanksCompany::TanksCompany(int id, PlanetBlackMarket* blackMarket) : PrintableObject(true)
{
	_blackMarket = blackMarket;
	_id = id;
	std::string tag = "[Tanks company #" + std::to_string(id) + "]: ";
	Print(tag.c_str(), "������");
}

void StarWarsSystem::TanksCompany::Run()
{
	std::string tag = "[Tanks company #" + std::to_string(_id) + "]: ";
	Print(tag.c_str(), "������ ������������ ������");
	int tanksCount = 0;
	std::string message;
	while (true)
	{
		tanksCount = _random.Next(1, MAX_TANKS_COUNT);
		message = "����������� " + std::to_string(tanksCount) + " ������. �������� �� ������ �����...";
		Print(tag.c_str(), message.c_str());
		_blackMarket->PostTanksSupply(tanksCount);
		Print(tag.c_str(), "������ ������ ��������� �� ������ �����.");
	}
}
