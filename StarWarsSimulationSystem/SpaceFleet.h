#pragma once

#include "starwarspch.h"
#include "FighterJet.h"
#include "Flagship.h"
#include <vector>
#include "Channel.h"

namespace StarWarsSystem
{
	class StarWarsObject SpaceFleet
	{
	private:
		SpaceShips::Flagship* _firstFlagship, * _secondFlagship;
		std::vector<SpaceShips::FighterJet*>* _fighterjets;
		int _fighterjetsCount;
		
	public:
		void Run();
		SpaceFleet();
	};
}

