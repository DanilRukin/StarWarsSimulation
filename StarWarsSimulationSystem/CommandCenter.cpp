#include "CommandCenter.h"

bool StarWarsSystem::CommandCenter::IsArmyStateOk(Report report) // оценивает состо€ние армии
{
	if (report.CurrentAmountOfClones < 0.4 * report.MaxAmountOfClones
		&& report.CurrentAmountOfTanks < 0.4 * report.MaxAmountOfTanks) // 60% потерь танков и клонов
		return false;
	else if (report.CurrentAmountOfClones < 0.1 * report.MaxAmountOfClones) // 90% потерь клонов
		return false;
	else if (report.CurrentAmountOfTanks < 0.1 * report.MaxAmountOfTanks) // 90% потерь танков
		return false;
	else
		return true;
}

bool StarWarsSystem::CommandCenter::IsFleetStateOk(Report report) // оценивает состо€ние флота
{
	if (report.FirstFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed
		&& report.SecondFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed)
		return false;
	else if ((report.FirstFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed
		|| report.SecondFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed) // один из флагманов уничтожен
		&& report.CurrentAmountOfFighterJets < 0.3 * report.MaxAmountOfFighterJets) // 70% потерь истребителей
		return false;
	else if (report.CurrentAmountOfFighterJets < 0.1 * report.MaxAmountOfFighterJets) // 90% потерь истребителей
		return false;
	else
		return true;
}

StarWarsSystem::CommandCenter::CommandCenter()
{
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC7 = new Core::Channel<CommandCenterOrder>(CHANNEL_C7_NAME);
	_channelC8 = new Core::Channel<CommandCenterOrder>(CHANNEL_C8_NAME);
	std::cout << _commandCenterTag << "командный центр создан" << std::endl;
}

void StarWarsSystem::CommandCenter::Run()
{
	std::cout << _commandCenterTag << "командный центр запущен" << std::endl;
	while (true)
	{
		//
		// ∆дем отчет от армии/флота
		//
		std::cout << _commandCenterTag << "ожидание отчета от армии/флота" << std::endl;
		Report reportFromFleetOrArmy = _channelC1->Get();
		//
		// ќценка состо€ни€ армии/флота
		//
		if (reportFromFleetOrArmy.ReportType == ReportType::FromFleet)
		{
			std::cout << _commandCenterTag << "получен отчет от флота" << std::endl;
			if (IsFleetStateOk(reportFromFleetOrArmy))
			{
				// приказ об отступлении
				std::cout << _commandCenterTag << "отправка приказа флоту об окончании атаки" << std::endl;
				_channelC7->Put(CommandCenterOrder::StopAttack);
			}
			else
			{
				// приказ о наступлении
				std::cout << _commandCenterTag
					<< "отправка приказа флоту о проведении атакующих действий" << std::endl;
				_channelC7->Put(CommandCenterOrder::StartAttack);
			}
		}
		else
		{
			// TODO: оценить состо€ние армии
			std::cout << _commandCenterTag << "получен отчет от армии" << std::endl;
			if (IsArmyStateOk(reportFromFleetOrArmy))
			{
				// приказ о наступлении
				std::cout << _commandCenterTag
					<< "отправка приказа армии о проведении атакующих действий" << std::endl;
				_channelC8->Put(CommandCenterOrder::StartAttack);
			}
			else
			{
				// приказ об отступлении
				std::cout << _commandCenterTag
					<< "отправка приказа армии об отступлении" << std::endl;
				_channelC8->Put(CommandCenterOrder::StopAttack);
			}
		}
	}
}
