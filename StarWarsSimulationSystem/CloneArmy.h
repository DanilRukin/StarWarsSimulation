#pragma once

#include "StarWarsAPI.h"
#include "Channel.h"
#include "CommandCenter.h"
#include "Report.h"
#include "GlabalNames.h"
#include <iostream>


namespace StarWarsSystem
{
	class StarWarsObject CloneArmy
	{
	private:
		Core::Channel<CommandCenterOrder>* _channelC8;
		Core::Channel<Report>* _channelC1;
		const char* _armyTag = "[Армия клонов]: ";
		int _amountOfClones, _amountOfTanks, _maxAmountOfClones, _maxAmountOfTanks;
		int _cloneWarriorHP, _tankHP;
		Report _stateReport;
	public:
		CloneArmy(int amountOfClones, int amountOfTanks);

		void Run();
	};

	//StarWarsObject DWORD WINAPI CloneArmyThread(LPVOID pVoid)
	//{
	//	Core::Channel<CommandCenterOrder>* _channelC8;
	//	Core::Channel<Report>* _channelC1;
	//	std::string _armyTag = "[Армия клонов]: ";
	//	int _amountOfClones, _amountOfTanks, _maxAmountOfClones, _maxAmountOfTanks;
	//	int _cloneWarriorHP, _tankHP;
	//	Report _stateReport;

	//	std::cout << _armyTag << "армия клонов запущена" << std::endl;
	//	CommandCenterOrder order;
	//	while (true)
	//	{
	//		// отправка отчета о состоянии в командный центр
	//		_stateReport = Report::ArmyReport(_amountOfClones, _maxAmountOfClones, _amountOfTanks, _maxAmountOfTanks);
	//		std::cout << _armyTag << "отчет создан" << std::endl;
	//		std::cout << _armyTag << "отчет отправляется в командный центр" << std::endl;
	//		_channelC1->Put(_stateReport);

	//		// ожидание приказа от командного центра
	//		std::cout << _armyTag << "ожидание приказа от командного центра" << std::endl;
	//		order = _channelC8->Get();
	//		std::cout << _armyTag << "приказ от командного центра получен" << std::endl;

	//		if (order == CommandCenterOrder::StopAttack)
	//		{
	//			std::cout << _armyTag << "остановка атаки" << std::endl;
	//			// TODO: stop attak
	//			std::cout << _armyTag << "атака остановлена" << std::endl;
	//		}
	//		else
	//		{
	//			std::cout << _armyTag << "проведение наступательного действия" << std::endl;
	//			// TODO: attack droid station

	//			// TODO: ожидать ответа от станции дроидов
	//			std::cout << _armyTag << "ожидание ответа от станции дроидов" << std::endl;

	//			std::cout << _armyTag << "ответ от станции дроидов получен, применение полученного урона" << std::endl;

	//		}
	//	}
	//}
}

