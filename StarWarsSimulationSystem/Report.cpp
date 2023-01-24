#include "Report.h"

StarWarsSystem::Report::Report()
{
	CurrentAmountOfFighterJets = 0;
	MaxAmountOfFighterJets = 0;
	FirstFlagshipStatus = SpaceShips::SpaceShipStatus::Ok;
	SecondFlagshipStatus = SpaceShips::SpaceShipStatus::Ok;
	MaxAmountOfClones = 0;
	MaxAmountOfTanks = 0;
	CurrentAmountOfClones = 0;
	CurrentAmountOfTanks = 0;
	ReportType = ReportType::FromArmy;
}

StarWarsSystem::Report StarWarsSystem::Report::FleetReport(int currentAmountOfFighterjets, int maxAmountOfFighterjets, SpaceShips::SpaceShipStatus firstFlagshipStatus, SpaceShips::SpaceShipStatus secondFlagshipStatus)
{
	Report report;
	report.ReportType = ReportType::FromFleet;
	report.CurrentAmountOfFighterJets = currentAmountOfFighterjets;
	report.MaxAmountOfFighterJets = maxAmountOfFighterjets;
	report.FirstFlagshipStatus = firstFlagshipStatus;
	report.SecondFlagshipStatus = secondFlagshipStatus;
	return report;
}

StarWarsSystem::Report StarWarsSystem::Report::ArmyReport(int currentAmountOfClones, int maxAmountOfClones, int currentAmountOfTanks, int maxAmountOfTanks)
{
	Report report;
	report.ReportType = ReportType::FromArmy;
	report.CurrentAmountOfClones = currentAmountOfClones;
	report.MaxAmountOfClones = maxAmountOfClones;
	report.CurrentAmountOfTanks = currentAmountOfTanks;
	report.MaxAmountOfTanks = maxAmountOfTanks;
	return report;
}
