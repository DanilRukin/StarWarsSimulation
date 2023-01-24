#pragma once
#include "StarWarsAPI.h"
#include "Channel.h"
#include <iostream>
#include "Report.h"
#include "GlabalNames.h"

namespace StarWarsSystem
{
	/**
	* Приказы командного центра
	*/
	enum StarWarsObject CommandCenterOrder
	{
		StartAttack, StopAttack
	};


	/**
	* Класс командного центра для удаленного управления армией клонов и космическим флотом.
	* Все наименования переменных соответствуют разработанной схеме.
	*/
	class StarWarsObject CommandCenter
	{
	private:
		/* Т.к. HANDLE канала открывается/создается по имени, то _channelC7 в этом классе будет указывать на тот же
		* объект, что и _channelC7 в классе флота.
		*/
		Core::Channel<CommandCenterOrder>* _channelC7; // канал для обмена данными с флотом
		Core::Channel<CommandCenterOrder>* _channelC8; // канал для обмена данным с армией
		Core::Channel<Report>* _channelC1; // канал для приема отчетов от армии/флота
		const char* _commandCenterTag = "[Command center]: ";

		bool IsArmyStateOk(Report report);

		bool IsFleetStateOk(Report report);
	public:
		CommandCenter();

		void Run();
	};

	//bool IsArmyStateOk(Report report) // оценивает состояние армии
	//{
	//	if (report.CurrentAmountOfClones < 0.4 * report.MaxAmountOfClones
	//		&& report.CurrentAmountOfTanks < 0.4 * report.MaxAmountOfTanks) // 60% потерь танков и клонов
	//		return false;
	//	else if (report.CurrentAmountOfClones < 0.1 * report.MaxAmountOfClones) // 90% потерь клонов
	//		return false;
	//	else if (report.CurrentAmountOfTanks < 0.1 * report.MaxAmountOfTanks) // 90% потерь танков
	//		return false;
	//	else
	//		return true;
	//}

	//bool IsFleetStateOk(Report report) // оценивает состояние флота
	//{
	//	if (report.FirstFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed
	//		&& report.SecondFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed)
	//		return false;
	//	else if ((report.FirstFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed
	//		|| report.SecondFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed) // один из флагманов уничтожен
	//		&& report.CurrentAmountOfFighterJets < 0.3 * report.MaxAmountOfFighterJets) // 70% потерь истребителей
	//		return false;
	//	else if (report.CurrentAmountOfFighterJets < 0.1 * report.MaxAmountOfFighterJets) // 90% потерь истребителей
	//		return false;
	//	else
	//		return true;
	//}

	//StarWarsObject DWORD WINAPI CommandCenterThread(LPVOID pVoid)
	//{
	//	Core::Channel<CommandCenterOrder>* _channelC7; // канал для обмена данными с флотом
	//	Core::Channel<CommandCenterOrder>* _channelC8; // канал для обмена данным с армией
	//	Core::Channel<Report>* _channelC1; // канал для приема отчетов от армии/флота
	//	std::string _commandCenterTag = "[Command center]: ";

	//	std::cout << _commandCenterTag << "командный центр запущен" << std::endl;
	//	while (true)
	//	{
	//		//
	//		// Ждем отчет от армии/флота
	//		//
	//		std::cout << _commandCenterTag << "ожидание отчета от армии/флота" << std::endl;
	//		Report reportFromFleetOrArmy = _channelC1->Get();
	//		//
	//		// Оценка состояния армии/флота
	//		//
	//		if (reportFromFleetOrArmy.ReportType == ReportType::FromFleet)
	//		{
	//			std::cout << _commandCenterTag << "получен отчет от флота" << std::endl;
	//			if (IsFleetStateOk(reportFromFleetOrArmy))
	//			{
	//				// приказ об отступлении
	//				std::cout << _commandCenterTag << "отправка приказа флоту об окончании атаки" << std::endl;
	//				_channelC7->Put(CommandCenterOrder::StopAttack);
	//			}
	//			else
	//			{
	//				// приказ о наступлении
	//				std::cout << _commandCenterTag
	//					<< "отправка приказа флоту о проведении атакующих действий" << std::endl;
	//				_channelC7->Put(CommandCenterOrder::StartAttack);
	//			}
	//		}
	//		else
	//		{
	//			// TODO: оценить состояние армии
	//			std::cout << _commandCenterTag << "получен отчет от армии" << std::endl;
	//			if (IsArmyStateOk(reportFromFleetOrArmy))
	//			{
	//				// приказ о наступлении
	//				std::cout << _commandCenterTag
	//					<< "отправка приказа армии о проведении атакующих действий" << std::endl;
	//				_channelC8->Put(CommandCenterOrder::StartAttack);
	//			}
	//			else
	//			{
	//				// приказ об отступлении
	//				std::cout << _commandCenterTag
	//					<< "отправка приказа армии об отступлении" << std::endl;
	//				_channelC8->Put(CommandCenterOrder::StopAttack);
	//			}
	//		}
	//	}
	//}
}

