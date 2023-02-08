#pragma once

#include "StarWarsAPI.h"
#include "Channel.h"
#include "CommandCenter.h"
#include "Report.h"
#include "GlabalNames.h"
#include <iostream>
#include "Damage.h"
#include "PrintableObject.h"


namespace StarWarsSystem
{
	class StarWarsObject CloneArmy : public PrintableObject
	{
	private:
		Core::Channel<CommandCenterOrder>* _channelC8;  // ��� ������ �������� �� ���������� ������
		Core::Channel<Report>* _channelC1; // ��� �������� ������ � ��������� �����
		Core::Channel<Damage>* _channelC2; // ��� ����� �� ������� �������
		Core::Channel<int>* _channelC4; // ��� ������ ������ �� ������� �������
		Core::Channel<int>* _channelC10; // ��� ������ ������������ �� ���������� ������
		const char* _armyTag = "[����� ������]: ";
		int _amountOfClones, _amountOfTanks, _maxAmountOfClones, _maxAmountOfTanks;
		int _cloneWarriorHP, _tankHP;
		int _cloneWarriorDamage, _tankDamage;
		int _waitReinforcementsTime;
		Report _stateReport;
	public:
		CloneArmy(int amountOfClones, int amountOfTanks, bool isMultiThread, int waitReinforcementsTime);
		~CloneArmy();
		Damage DoDamageForDroidStation();
		void AcceptDamage(int damage);
		void AcceptReinforcements(int reinforcements);
		void Run();
	};
}

