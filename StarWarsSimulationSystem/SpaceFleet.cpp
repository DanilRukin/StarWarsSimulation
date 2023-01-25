#include "SpaceFleet.h"

StarWarsSystem::SpaceFleet::SpaceFleet()
{
	SpaceShips::SpaceShipsFactory factory;
	_firstFlagship = factory.CreateFlagship();
	_secondFlagship = factory.CreateFlagship();
	_fighterjetsCount = 100;
	_fighterjets = new SpaceShips::FighterJet * [_fighterjetsCount];
	for (int i = 0; i < _fighterjetsCount; i++)
	{
		_fighterjets[i] = factory.CreateFighterJet();
	}
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC7 = new Core::Channel<CommandCenterOrder>(CHANNEL_C7_NAME);
}

void StarWarsSystem::SpaceFleet::Run()
{

}
