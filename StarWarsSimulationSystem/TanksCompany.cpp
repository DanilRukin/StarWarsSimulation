#include "TanksCompany.h"

StarWarsSystem::TanksCompany::TanksCompany(int id, PlanetBlackMarket* blackMarket) : ReadWriteLockObject(true)
{
	_blackMarket = blackMarket;
	_id = id;
	std::string tag = "[Tanks company #" + std::to_string(id) + "]: ";
	Print(tag.c_str(), "создан");
}

void StarWarsSystem::TanksCompany::Run()
{
	std::string tag = "[Tanks company #" + std::to_string(_id) + "]: ";
	Print(tag.c_str(), "Запуск производства танков");
	int tanksCount = 0;
	std::string message;
	while (true)
	{
		tanksCount = _random.Next(1, MAX_TANKS_COUNT);
		message = "Произведено " + std::to_string(tanksCount) + " танков. Отправка на черный рынок...";
		Print(tag.c_str(), message.c_str());
		_e->WaitOne(); // ждем эстафету на ввод запроса
		if (NUM_R > 0 || NUM_W > 0)
		{
			WAIT_W++; // появился еще один ожидающий писатель
			_e->Release();
			_w->WaitOne(); // ждем эстафету на запись
		}
		NUM_W++;
		Estafeta(); // эстафету получили - работаем! 
		_blackMarket->PostTanksSupply(tanksCount);
		Print(tag.c_str(), "партия танков размещена на черном рынке.");
		_e->WaitOne(); // ждем эстафету - отметить конец
		NUM_W--;
		Estafeta();
	}
}
