#include "CloneArmy.h"

StarWarsSystem::CloneArmy::CloneArmy(int amountOfClones, int amountOfTanks)
{
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC8 = new Core::Channel<CommandCenterOrder>(CHANNEL_C8_NAME);
	_amountOfClones = amountOfClones;
	_maxAmountOfClones = amountOfClones;
	_amountOfTanks = amountOfTanks;
	_maxAmountOfTanks = amountOfTanks;
	_cloneWarriorHP = 100;
	_tankHP = 10000;
	std::cout << _armyTag << "армия клонов создана" << std::endl;
}

void StarWarsSystem::CloneArmy::Run()
{
	std::cout << _armyTag << "армия клонов запущена" << std::endl;
	CommandCenterOrder order;
	while (true)
	{
		// отправка отчета о состоянии в командный центр
		_stateReport = Report::ArmyReport(_amountOfClones, _maxAmountOfClones, _amountOfTanks, _maxAmountOfTanks);
		std::cout << _armyTag << "отчет создан" << std::endl;
		std::cout << _armyTag << "отчет отправляется в командный центр" << std::endl;
		_channelC1->Put(_stateReport);

		// ожидание приказа от командного центра
		std::cout << _armyTag << "ожидание приказа от командного центра" << std::endl;
		order = _channelC8->Get();
		std::cout << _armyTag << "приказ от командного центра получен" << std::endl;

		if (order == CommandCenterOrder::StopAttack)
		{
			std::cout << _armyTag << "остановка атаки" << std::endl;
			// TODO: stop attak
			std::cout << _armyTag << "атака остановлена" << std::endl;
		}
		else
		{
			std::cout << _armyTag << "проведение наступательного действия" << std::endl;
			// TODO: attack droid station

			// TODO: ожидать ответа от станции дроидов
			std::cout << _armyTag << "ожидание ответа от станции дроидов" << std::endl;

			std::cout << _armyTag << "ответ от станции дроидов получен, применение полученного урона" << std::endl;

		}
	}
}
