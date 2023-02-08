#include "CommandCenter.h"

bool StarWarsSystem::CommandCenter::IsArmyStateOk(Report report) // оценивает состояние армии
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

bool StarWarsSystem::CommandCenter::IsFleetStateOk(Report report) // оценивает состояние флота
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

StarWarsSystem::CommandCenter::CommandCenter(bool isMultiThread, PlanetBlackMarket* blackMarket) : PrintableObject(isMultiThread)
{
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC7 = new Core::Channel<CommandCenterOrder>(CHANNEL_C7_NAME);
	_channelC8 = new Core::Channel<CommandCenterOrder>(CHANNEL_C8_NAME);
	_channelC9 = new Core::Channel<int>(CHANNEL_C9_NAME);
	_channelC10 = new Core::Channel<int>(CHANNEL_C10_NAME);
	_blackMarket = blackMarket;
	Print(_commandCenterTag, "командный центр создан");
}

void StarWarsSystem::CommandCenter::Run()
{
	Print(_commandCenterTag, "командный центр запущен");
	int additionalSpaceShips = 0;
	int additionalTanks = 0;
	std::string message;
	while (true)
	{
		Print(_commandCenterTag, "ожидание отчета от армии/флота");
		Report reportFromFleetOrArmy;
		Core::ChannelResult<Report> reportResult;
		reportResult  = _channelC1->Get();
		reportFromFleetOrArmy = reportResult.Data;
		if (reportFromFleetOrArmy.ReportType == ReportType::FromFleet)
		{
			Print(_commandCenterTag, "получен отчет от флота");
			if (IsFleetStateOk(reportFromFleetOrArmy))
			{
				// приказ об отступлении
				Print(_commandCenterTag, "отправка приказа флоту об окончании атаки");
				_channelC7->Put(CommandCenterOrder::StopAttack);
				if (_blackMarket != nullptr)
				{
					Print(_commandCenterTag, "Закупка дополнительного вооружения для флота на черном рынке");
					additionalSpaceShips = _blackMarket->BuySpaceShipSupply();
					message = "Дополнительное вооружение для флота в количестве [" + std::to_string(additionalSpaceShips) + "] закуплено. Отправка...";
					Print(_commandCenterTag, message.c_str());

					_channelC9->Put(additionalSpaceShips); // отправка вооружений					
				}
			}
			else
			{
				// приказ о наступлении
				Print(_commandCenterTag, "отправка приказа флоту о проведении атакующих действий");
				_channelC7->Put(CommandCenterOrder::StartAttack);								
			}
		}
		else
		{
			Print(_commandCenterTag, "получен отчет от армии");
			if (IsArmyStateOk(reportFromFleetOrArmy))
			{
				// приказ о наступлении
				Print(_commandCenterTag, "отправка приказа армии о проведении атакующих действий");
				_channelC8->Put(CommandCenterOrder::StartAttack);
			}
			else
			{
				// приказ об отступлении
				Print(_commandCenterTag, "отправка приказа армии об отступлении");
				_channelC8->Put(CommandCenterOrder::StopAttack);
				if (_blackMarket != nullptr)
				{
					Print(_commandCenterTag, "Закупка дополнительного вооружения для армии клонов на черном рынке");
					additionalTanks = _blackMarket->BuyTanksSupply();
					message = "Дополнительное вооружение для армии в количестве [" + std::to_string(additionalTanks) + "] закуплено. Отправка...";
					Print(_commandCenterTag, message.c_str());

					_channelC10->Put(additionalTanks); // отправка вооружений					
				}
			}
		}
	}
}
