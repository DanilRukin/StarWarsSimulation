#include <iostream>
#include "GlabalNames.h"
#include <TradeFederation.h>
#include <DroidStation.h>
#include <SpaceFleet.h>
#include <CloneArmy.h>
#include "PlanetBlackMarketRWL.h"
#include "TanksCompany.h"
#include "SpaceShipsCompany.h"

using namespace StarWarsSystem;

CloneArmy* army;
SpaceFleet* fleet;
CommandCenter* commandCenter;
DroidStation* station;
TradeFederation* federation;

PlanetBlackMarketRWL* blackMarket;

TanksCompany* firstTanksCompany;
TanksCompany* secondTanksCompany;

SpaceShipsComapny* firstSpaceShipsCompany;
SpaceShipsComapny* secondSpaceShipsCompany;

/**
* Обертка для вызова метода Run() командного центра [по-другому в C++ нельзя]
*/
DWORD WINAPI CommandCenterRun(LPVOID pVoid)
{
    commandCenter->Run();
    return 0;
}
/**
* Обертка для вызова метода Run() армии клонов [по-другому в C++ нельзя]
*/
DWORD WINAPI ArmyRun(LPVOID pVoid)
{
    army->Run();
    return 0;
}

/**
* Обертка для вызова метода Run() космического флота [по-другому в C++ нельзя]
*/
DWORD WINAPI FleetRun(LPVOID pVoid)
{
    fleet->Run();
    return 0;
}

/**
* Обертка для вызова метода Run() станции дроидов [по-другому в C++ нельзя]
*/
DWORD WINAPI DroidStationRun(LPVOID pVoid)
{
    station->Run();
    return 0;
}

/**
* Обертка для вызова метода Run() торговой федерации [по-другому в C++ нельзя]
*/
DWORD WINAPI TradeFederationRun(LPVOID pVoid)
{
    federation->Run();
    return 0;
}

/**
* Обертка для вызова метода Run() первого завода по производству наземеных вооружений [по-другому в C++ нельзя]
*/
DWORD WINAPI FirstTanksCompanyRun(LPVOID pVoid)
{
    firstTanksCompany->Run();
    return 0;
}

/**
* Обертка для вызова метода Run() второго завода по производству наземеных вооружений [по-другому в C++ нельзя]
*/
DWORD WINAPI SecondTanksCompanyRun(LPVOID pVoid)
{
    secondTanksCompany->Run();
    return 0;
}

/**
* Обертка для вызова метода Run() первого завода по производству космических вооружений [по-другому в C++ нельзя]
*/
DWORD WINAPI FirstSpaceShipsCompanyRun(LPVOID pVoid)
{
    firstSpaceShipsCompany->Run();
    return 0;
}

/**
* Обертка для вызова метода Run() второго завода по производству космических вооружений [по-другому в C++ нельзя]
*/
DWORD WINAPI SecondSpaceShipsCompanyRun(LPVOID pVoid)
{
    secondSpaceShipsCompany->Run();
    return 0;
}


int main()
{
    setlocale(LC_ALL, "ru");

    bool isMultiThread = true;
    HANDLE commandCenterThread, cloneArmyThread, fleetThread, droidStationThread, tradeFederationThread, firstTanksCompanyThread,
        secondTanksCompanyThread, firstSpaceShipsComapnyThread, secondSpaceShipsComapnyThread;
    DWORD commandCenterThreadId, cloneArmyThreadId, fleetThreadId, droidStationThreadId, tradeFederationThreadId, firstTanksCompanyThreadId,
        secondTanksCompanyThreadId, firstSpaceShipsComapnyThreadId, secondSpaceShipsComapnyThreadId;

    blackMarket = new PlanetBlackMarketRWL(10, 10);

    army = new CloneArmy(100, 10, isMultiThread, 30000);
    fleet = new SpaceFleet(isMultiThread, 30000);
    commandCenter = new CommandCenter(isMultiThread, blackMarket);
    station = new DroidStation(1000, 100, 50, isMultiThread, 30000);
    federation = new TradeFederation(100, 50, isMultiThread, blackMarket);

    firstSpaceShipsCompany = new SpaceShipsComapny(1, blackMarket);
    secondSpaceShipsCompany = new SpaceShipsComapny(2, blackMarket);
    firstTanksCompany = new TanksCompany(1, blackMarket);
    secondTanksCompany = new TanksCompany(2, blackMarket);

    std::cout << "Запуск потоков" << std::endl;

    commandCenterThread = CreateThread(nullptr, 0, CommandCenterRun, (void*)nullptr, 0, &commandCenterThreadId);
    cloneArmyThread = CreateThread(nullptr, 0, ArmyRun, (void*)nullptr, 0, &cloneArmyThreadId);
    fleetThread = CreateThread(nullptr, 0, FleetRun, (void*)nullptr, 0, &fleetThreadId);
    droidStationThread = CreateThread(nullptr, 0, DroidStationRun, (void*)nullptr, 0, &droidStationThreadId);
    tradeFederationThread = CreateThread(nullptr, 0, TradeFederationRun, (void*)nullptr, 0, &tradeFederationThreadId);

    firstTanksCompanyThread = CreateThread(nullptr, 0, FirstTanksCompanyRun, (void*)nullptr, 0, &firstTanksCompanyThreadId);
    secondTanksCompanyThread = CreateThread(nullptr, 0, SecondTanksCompanyRun, (void*)nullptr, 0, &secondTanksCompanyThreadId);
    firstSpaceShipsComapnyThread = CreateThread(nullptr, 0, FirstSpaceShipsCompanyRun, (void*)nullptr, 0, &firstSpaceShipsComapnyThreadId);
    secondSpaceShipsComapnyThread = CreateThread(nullptr, 0, SecondSpaceShipsCompanyRun, (void*)nullptr, 0, &secondSpaceShipsComapnyThreadId);
    

    std::cout << "Потоки запущены" << std::endl;

    WaitForSingleObject(commandCenterThread, INFINITE);
    WaitForSingleObject(cloneArmyThread, INFINITE);
    WaitForSingleObject(fleetThread, INFINITE);
    WaitForSingleObject(droidStationThread, INFINITE);
    WaitForSingleObject(tradeFederationThread, INFINITE);
    WaitForSingleObject(firstTanksCompanyThread, INFINITE);
    WaitForSingleObject(secondTanksCompanyThread, INFINITE);
    WaitForSingleObject(firstSpaceShipsComapnyThread, INFINITE);
    WaitForSingleObject(secondSpaceShipsComapnyThread, INFINITE);

    std::cout << "Конец работы" << std::endl;
    return 0;
}
