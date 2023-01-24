#pragma once

#include "StarWarsAPI.h"
#include "SpaceShip.h"

namespace StarWarsSystem
{
	enum StarWarsObject ReportType
	{
		FromArmy, FromFleet
	};

	class StarWarsObject Report
	{
	public:
		ReportType ReportType;
		//
		// Отчетность для флота
		//
		int CurrentAmountOfFighterJets;
		int MaxAmountOfFighterJets;

		SpaceShips::SpaceShipStatus FirstFlagshipStatus;
		SpaceShips::SpaceShipStatus SecondFlagshipStatus;
		//
		// Отчетность для армии
		//
		int MaxAmountOfClones, CurrentAmountOfClones;
		int MaxAmountOfTanks, CurrentAmountOfTanks;

		Report();

		static Report FleetReport(int currentAmountOfFighterjets, int maxAmountOfFighterjets,
			SpaceShips::SpaceShipStatus firstFlagshipStatus, SpaceShips::SpaceShipStatus secondFlagshipStatus);

		static Report ArmyReport(int currentAmountOfClones, int maxAmountOfClones, 
			int currentAmountOfTanks, int maxAmountOfTanks);
	};
}

