#pragma once
#include "StarWarsAPI.h"
#include "FighterJet.h"
#include "Flagship.h"
#include "Channel.h"
#include "SpaceShipsFactory.h"
#include "CommandCenter.h"
#include "Report.h"
#include "GlabalNames.h"
#include "Damage.h"
#include "PrintableObject.h"

namespace StarWarsSystem
{
	class StarWarsObject SpaceFleet : public PrintableObject
	{
	private:
		int _fighterjetsCount;
		SpaceShips::Flagship* _firstFlagship, * _secondFlagship;
		SpaceShips::FighterJet** _fighterjets;
		
		Core::Channel<Report>* _channelC1; // канал для приема отчетов от армии/флота;
		Core::Channel<Damage>* _channelC2; // для атаки на станцию дроидов
		Core::Channel<int>* _channelC3; // прием урона от станции дроидов
		Core::Channel<CommandCenterOrder>* _channelC7; // для приема приказов от командного центра

		const char* _spaceFleetTag = "[Space Fleet]: ";
	public:
		
		SpaceFleet(bool isMultiThread);
		~SpaceFleet();
		Damage DoDamageForDroidStation();
		void AcceptDamage(int damage);
		void Run();
	};
}

