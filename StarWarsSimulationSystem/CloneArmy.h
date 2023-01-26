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
		Core::Channel<CommandCenterOrder>* _channelC8;  // для приема приказов из командного центра
		Core::Channel<Report>* _channelC1; // для отправки отчета в командный центр
		Core::Channel<Damage>* _channelC2; // для атаки на станцию дроидов
		Core::Channel<int>* _channelC4; // для приема ответа от станции дроидов
		const char* _armyTag = "[Армия клонов]: ";
		int _amountOfClones, _amountOfTanks, _maxAmountOfClones, _maxAmountOfTanks;
		int _cloneWarriorHP, _tankHP;
		int _cloneWarriorDamage, _tankDamage;
		Report _stateReport;
	public:
		CloneArmy(int amountOfClones, int amountOfTanks, bool isMultiThread);
		~CloneArmy();
		Damage DoDamageForDroidStation();
		void AcceptDamage(int damage);
		void Run();
	};
}

