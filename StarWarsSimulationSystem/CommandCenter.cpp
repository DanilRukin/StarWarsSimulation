#include "CommandCenter.h"

bool StarWarsSystem::CommandCenter::IsArmyStateOk(Report report) // ��������� ��������� �����
{
	if (report.CurrentAmountOfClones < 0.4 * report.MaxAmountOfClones
		&& report.CurrentAmountOfTanks < 0.4 * report.MaxAmountOfTanks) // 60% ������ ������ � ������
		return false;
	else if (report.CurrentAmountOfClones < 0.1 * report.MaxAmountOfClones) // 90% ������ ������
		return false;
	else if (report.CurrentAmountOfTanks < 0.1 * report.MaxAmountOfTanks) // 90% ������ ������
		return false;
	else
		return true;
}

bool StarWarsSystem::CommandCenter::IsFleetStateOk(Report report) // ��������� ��������� �����
{
	if (report.FirstFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed
		&& report.SecondFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed)
		return false;
	else if ((report.FirstFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed
		|| report.SecondFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed) // ���� �� ��������� ���������
		&& report.CurrentAmountOfFighterJets < 0.3 * report.MaxAmountOfFighterJets) // 70% ������ ������������
		return false;
	else if (report.CurrentAmountOfFighterJets < 0.1 * report.MaxAmountOfFighterJets) // 90% ������ ������������
		return false;
	else
		return true;
}

StarWarsSystem::CommandCenter::CommandCenter(bool isMultiThread) : PrintableObject(isMultiThread)
{
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC7 = new Core::Channel<CommandCenterOrder>(CHANNEL_C7_NAME);
	_channelC8 = new Core::Channel<CommandCenterOrder>(CHANNEL_C8_NAME);
	Print(_commandCenterTag, "��������� ����� ������");
	// std::cout << _commandCenterTag << "��������� ����� ������" << std::endl;
}

void StarWarsSystem::CommandCenter::Run()
{
	Print(_commandCenterTag, "��������� ����� �������");
	// std::cout << _commandCenterTag << "��������� ����� �������" << std::endl;
	while (true)
	{
		Print(_commandCenterTag, "�������� ������ �� �����/�����");
		// std::cout << _commandCenterTag << "�������� ������ �� �����/�����" << std::endl;
		Report reportFromFleetOrArmy;
		Core::ChannelResult<Report> reportResult;
		reportResult  = _channelC1->Get();
		reportFromFleetOrArmy = reportResult.Data;
		if (reportFromFleetOrArmy.ReportType == ReportType::FromFleet)
		{
			Print(_commandCenterTag, "������� ����� �� �����");
			// std::cout << _commandCenterTag << "������� ����� �� �����" << std::endl;
			if (IsFleetStateOk(reportFromFleetOrArmy))
			{
				// ������ �� �����������
				Print(_commandCenterTag, "�������� ������� ����� �� ��������� �����");
				// std::cout << _commandCenterTag << "�������� ������� ����� �� ��������� �����" << std::endl;
				_channelC7->Put(CommandCenterOrder::StopAttack);
			}
			else
			{
				// ������ � �����������
				Print(_commandCenterTag, "�������� ������� ����� � ���������� ��������� ��������");
				/*std::cout << _commandCenterTag
					<< "�������� ������� ����� � ���������� ��������� ��������" << std::endl;*/
				_channelC7->Put(CommandCenterOrder::StartAttack);
			}
		}
		else
		{
			Print(_commandCenterTag, "������� ����� �� �����");
			// std::cout << _commandCenterTag << "������� ����� �� �����" << std::endl;
			if (IsArmyStateOk(reportFromFleetOrArmy))
			{
				// ������ � �����������
				Print(_commandCenterTag, "�������� ������� ����� � ���������� ��������� ��������");
				/*std::cout << _commandCenterTag
					<< "�������� ������� ����� � ���������� ��������� ��������" << std::endl;*/
				_channelC8->Put(CommandCenterOrder::StartAttack);
			}
			else
			{
				// ������ �� �����������
				Print(_commandCenterTag, "�������� ������� ����� �� �����������");
				/*std::cout << _commandCenterTag
					<< "�������� ������� ����� �� �����������" << std::endl;*/
				_channelC8->Put(CommandCenterOrder::StopAttack);
			}
		}
	}
}
