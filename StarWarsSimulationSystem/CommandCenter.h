#pragma once
#include "StarWarsAPI.h"
#include "Channel.h"
#include <iostream>
#include "Report.h"
#include "GlabalNames.h"
#include "PrintableObject.h"

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
	class StarWarsObject CommandCenter : public PrintableObject
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
		CommandCenter(bool isMultiThread);

		void Run();
	};
}

