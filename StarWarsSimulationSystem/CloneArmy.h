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
		const char* _armyTag = "[����� ������]: ";
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
	//	std::string _armyTag = "[����� ������]: ";
	//	int _amountOfClones, _amountOfTanks, _maxAmountOfClones, _maxAmountOfTanks;
	//	int _cloneWarriorHP, _tankHP;
	//	Report _stateReport;

	//	std::cout << _armyTag << "����� ������ ��������" << std::endl;
	//	CommandCenterOrder order;
	//	while (true)
	//	{
	//		// �������� ������ � ��������� � ��������� �����
	//		_stateReport = Report::ArmyReport(_amountOfClones, _maxAmountOfClones, _amountOfTanks, _maxAmountOfTanks);
	//		std::cout << _armyTag << "����� ������" << std::endl;
	//		std::cout << _armyTag << "����� ������������ � ��������� �����" << std::endl;
	//		_channelC1->Put(_stateReport);

	//		// �������� ������� �� ���������� ������
	//		std::cout << _armyTag << "�������� ������� �� ���������� ������" << std::endl;
	//		order = _channelC8->Get();
	//		std::cout << _armyTag << "������ �� ���������� ������ �������" << std::endl;

	//		if (order == CommandCenterOrder::StopAttack)
	//		{
	//			std::cout << _armyTag << "��������� �����" << std::endl;
	//			// TODO: stop attak
	//			std::cout << _armyTag << "����� �����������" << std::endl;
	//		}
	//		else
	//		{
	//			std::cout << _armyTag << "���������� ��������������� ��������" << std::endl;
	//			// TODO: attack droid station

	//			// TODO: ������� ������ �� ������� �������
	//			std::cout << _armyTag << "�������� ������ �� ������� �������" << std::endl;

	//			std::cout << _armyTag << "����� �� ������� ������� �������, ���������� ����������� �����" << std::endl;

	//		}
	//	}
	//}
}

