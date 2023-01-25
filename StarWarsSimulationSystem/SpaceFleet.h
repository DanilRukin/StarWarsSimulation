#pragma once
#include "StarWarsAPI.h"
#include "FighterJet.h"
#include "Flagship.h"
#include "Channel.h"
#include "SpaceShipsFactory.h"
#include "CommandCenter.h"
#include "Report.h"
#include "GlabalNames.h"

namespace StarWarsSystem
{
	class StarWarsObject SpaceFleet
	{
	private:
		int _fighterjetsCount;
		SpaceShips::Flagship* _firstFlagship, * _secondFlagship;
		SpaceShips::FighterJet** _fighterjets;
		
		Core::Channel<Report>* _channelC1; // канал для приема отчетов от армии/флота;
		Core::Channel<CommandCenterOrder>* _channelC7; // канал для обмена данными с флотом
	public:
		
		SpaceFleet();

		void Run();
	};
}

