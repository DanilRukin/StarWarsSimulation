#pragma once
#include "StarWarsAPI.h"
#include "FighterJet.h"
#include "Flagship.h"
#include <vector>
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
		SpaceShips::Flagship* _firstFlagship, * _secondFlagship;
		std::vector<SpaceShips::FighterJet*>* _fighterjets;
		int _fighterjetsCount;
		Core::Channel<Report>* _channelC1; // канал для приема отчетов от армии/флота;
		Core::Channel<CommandCenterOrder>* _channelC7; // канал для обмена данными с флотом
	public:
		
		SpaceFleet();

		void Run();
	};
}

