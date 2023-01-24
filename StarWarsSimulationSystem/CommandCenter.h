#pragma once
#include "StarWarsAPI.h"
#include "Channel.h"
#include <iostream>
#include "Report.h"
#include "GlabalNames.h"

namespace StarWarsSystem
{
	/**
	* ������� ���������� ������
	*/
	enum StarWarsObject CommandCenterOrder
	{
		StartAttack, StopAttack
	};


	/**
	* ����� ���������� ������ ��� ���������� ���������� ������ ������ � ����������� ������.
	* ��� ������������ ���������� ������������� ������������� �����.
	*/
	class StarWarsObject CommandCenter
	{
	private:
		/* �.�. HANDLE ������ �����������/��������� �� �����, �� _channelC7 � ���� ������ ����� ��������� �� ��� ��
		* ������, ��� � _channelC7 � ������ �����.
		*/
		Core::Channel<CommandCenterOrder>* _channelC7; // ����� ��� ������ ������� � ������
		Core::Channel<CommandCenterOrder>* _channelC8; // ����� ��� ������ ������ � ������
		Core::Channel<Report>* _channelC1; // ����� ��� ������ ������� �� �����/�����
		const char* _commandCenterTag = "[Command center]: ";

		bool IsArmyStateOk(Report report);

		bool IsFleetStateOk(Report report);
	public:
		CommandCenter();

		void Run();
	};

	//bool IsArmyStateOk(Report report) // ��������� ��������� �����
	//{
	//	if (report.CurrentAmountOfClones < 0.4 * report.MaxAmountOfClones
	//		&& report.CurrentAmountOfTanks < 0.4 * report.MaxAmountOfTanks) // 60% ������ ������ � ������
	//		return false;
	//	else if (report.CurrentAmountOfClones < 0.1 * report.MaxAmountOfClones) // 90% ������ ������
	//		return false;
	//	else if (report.CurrentAmountOfTanks < 0.1 * report.MaxAmountOfTanks) // 90% ������ ������
	//		return false;
	//	else
	//		return true;
	//}

	//bool IsFleetStateOk(Report report) // ��������� ��������� �����
	//{
	//	if (report.FirstFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed
	//		&& report.SecondFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed)
	//		return false;
	//	else if ((report.FirstFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed
	//		|| report.SecondFlagshipStatus == SpaceShips::SpaceShipStatus::Destroyed) // ���� �� ��������� ���������
	//		&& report.CurrentAmountOfFighterJets < 0.3 * report.MaxAmountOfFighterJets) // 70% ������ ������������
	//		return false;
	//	else if (report.CurrentAmountOfFighterJets < 0.1 * report.MaxAmountOfFighterJets) // 90% ������ ������������
	//		return false;
	//	else
	//		return true;
	//}

	//StarWarsObject DWORD WINAPI CommandCenterThread(LPVOID pVoid)
	//{
	//	Core::Channel<CommandCenterOrder>* _channelC7; // ����� ��� ������ ������� � ������
	//	Core::Channel<CommandCenterOrder>* _channelC8; // ����� ��� ������ ������ � ������
	//	Core::Channel<Report>* _channelC1; // ����� ��� ������ ������� �� �����/�����
	//	std::string _commandCenterTag = "[Command center]: ";

	//	std::cout << _commandCenterTag << "��������� ����� �������" << std::endl;
	//	while (true)
	//	{
	//		//
	//		// ���� ����� �� �����/�����
	//		//
	//		std::cout << _commandCenterTag << "�������� ������ �� �����/�����" << std::endl;
	//		Report reportFromFleetOrArmy = _channelC1->Get();
	//		//
	//		// ������ ��������� �����/�����
	//		//
	//		if (reportFromFleetOrArmy.ReportType == ReportType::FromFleet)
	//		{
	//			std::cout << _commandCenterTag << "������� ����� �� �����" << std::endl;
	//			if (IsFleetStateOk(reportFromFleetOrArmy))
	//			{
	//				// ������ �� �����������
	//				std::cout << _commandCenterTag << "�������� ������� ����� �� ��������� �����" << std::endl;
	//				_channelC7->Put(CommandCenterOrder::StopAttack);
	//			}
	//			else
	//			{
	//				// ������ � �����������
	//				std::cout << _commandCenterTag
	//					<< "�������� ������� ����� � ���������� ��������� ��������" << std::endl;
	//				_channelC7->Put(CommandCenterOrder::StartAttack);
	//			}
	//		}
	//		else
	//		{
	//			// TODO: ������� ��������� �����
	//			std::cout << _commandCenterTag << "������� ����� �� �����" << std::endl;
	//			if (IsArmyStateOk(reportFromFleetOrArmy))
	//			{
	//				// ������ � �����������
	//				std::cout << _commandCenterTag
	//					<< "�������� ������� ����� � ���������� ��������� ��������" << std::endl;
	//				_channelC8->Put(CommandCenterOrder::StartAttack);
	//			}
	//			else
	//			{
	//				// ������ �� �����������
	//				std::cout << _commandCenterTag
	//					<< "�������� ������� ����� �� �����������" << std::endl;
	//				_channelC8->Put(CommandCenterOrder::StopAttack);
	//			}
	//		}
	//	}
	//}
}

