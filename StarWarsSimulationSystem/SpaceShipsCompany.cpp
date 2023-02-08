#include "SpaceShipsCompany.h"

StarWarsSystem::SpaceShipsComapny::SpaceShipsComapny(int id, PlanetBlackMarket* blackMarket) : PrintableObject(true)
{
	_blackMarket = blackMarket;
	_id = id;
	std::string tag = "[Space ships conpany #" + std::to_string(id) + "]: ";
	Print(tag.c_str(), "создан");
}

void StarWarsSystem::SpaceShipsComapny::Run()
{
	std::string tag = "[Space ships conpany #" + std::to_string(_id) + "]: ";
	Print(tag.c_str(), "Запуск производства средств ПВО/космических кораблей");
	int spaceShipsCount = 0;
	std::string message;
	while (true)
	{
		spaceShipsCount = _random.Next(1, MAX_SHIPS_COUNT);
		message = "Произведено " + std::to_string(spaceShipsCount) + " ед. космического вооружения. Отправка на черный рынок...";
		Print(tag.c_str(), message.c_str());
		_blackMarket->PostSpaceShipsSupply(spaceShipsCount);
		Print(tag.c_str(), "партия космического вооружения размещена на черном рынке.");
	}
}
