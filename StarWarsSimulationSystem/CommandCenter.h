#pragma once
#include "StarWarsAPI.h"
#include "Channel.h"
#include <iostream>
#include "Report.h"
#include "GlabalNames.h"
#include "PrintableObject.h"
#include "PlanetBlackMarket.h"
#include "ReadWriteLockObject.h"

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
	class StarWarsObject CommandCenter : public ReadWriteLockObject
	{
	private:
		/* �.�. HANDLE ������ �����������/��������� �� �����, �� _channelC7 � ���� ������ ����� ��������� �� ��� ��
		* ������, ��� � _channelC7 � ������ �����.
		*/
		Core::Channel<CommandCenterOrder>* _channelC7; // ����� ��� ������ ������� � ������
		Core::Channel<CommandCenterOrder>* _channelC8; // ����� ��� ������ ������ � ������
		Core::Channel<Report>* _channelC1; // ����� ��� ������ ������� �� �����/�����
		Core::Channel<int>* _channelC9; // ����� ��� �������� ���. ���������� ������������ �����
		Core::Channel<int>* _channelC10; // ����� ��� �������� ���. ���������� ����� ������
		const char* _commandCenterTag = "[Command center]: ";
		PlanetBlackMarket* _blackMarket = nullptr;

		bool IsArmyStateOk(Report report);

		bool IsFleetStateOk(Report report);
	public:
		CommandCenter(bool isMultiThread, PlanetBlackMarket* blackMarket = nullptr);

		void Run();
	};
}

