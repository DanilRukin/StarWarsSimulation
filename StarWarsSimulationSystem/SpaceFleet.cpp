#include "starwarspch.h"
#include "SpaceFleet.h"
#include "SpaceShipsFactory.h"

void StarWarsSystem::SpaceFleet::Run()
{

}

StarWarsSystem::SpaceFleet::SpaceFleet()
{
	SpaceShips::SpaceShipsFactory factory;
	_firstFlagship = factory.CreateFlagship();
	_secondFlagship = factory.CreateFlagship();
	_fighterjetsCount = 100;
	_fighterjets = new std::vector<SpaceShips::FighterJet*>(_fighterjetsCount);
	for (int i = 0; i < _fighterjetsCount; i++)
	{
		_fighterjets->push_back(factory.CreateFighterJet());
	}
}
