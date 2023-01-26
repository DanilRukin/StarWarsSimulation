#include <iostream>
#include "CloneArmy.h"
#include "CommandCenter.h"
#include "SpaceFleet.h"
#include "DroidStation.h"
#include "TradeFederation.h"

using namespace StarWarsSystem;

CloneArmy* army;
SpaceFleet* fleet;
CommandCenter* commandCenter;
DroidStation* station;
TradeFederation* federation;
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

int main()
{
    setlocale(LC_ALL, "ru");
    bool isMultiThread = true;
    HANDLE commandCenterThread, cloneArmyThread, fleetThread, droidStationThread, tradeFederationThread;
    DWORD commandCenterThreadId, cloneArmyThreadId, fleetThreadId, droidStationThreadId, tradeFederationThreadId;
    army = new CloneArmy(100, 10, isMultiThread);
    fleet = new SpaceFleet(isMultiThread);
    commandCenter = new CommandCenter(isMultiThread);
    station = new DroidStation(1000000, 10000, 5000, isMultiThread, 30000);
    federation = new TradeFederation(10000000, 10000000, isMultiThread);
    std::cout << "Запуск потоков" << std::endl;
    cloneArmyThread = CreateThread(nullptr, 0, ArmyRun, (void*)nullptr, 0, &cloneArmyThreadId);
    commandCenterThread = CreateThread(nullptr, 0, CommandCenterRun, (void*)nullptr, 0, &commandCenterThreadId);
    fleetThread = CreateThread(nullptr, 0, FleetRun, (void*)nullptr, 0, &fleetThreadId);
    droidStationThread = CreateThread(nullptr, 0, DroidStationRun, (void*)nullptr, 0, &droidStationThreadId);
    tradeFederationThread = CreateThread(nullptr, 0, TradeFederationRun, (void*)nullptr, 0, &tradeFederationThreadId);
    std::cout << "Потоки запущены" << std::endl;
    WaitForSingleObject(commandCenterThread, INFINITE);
    WaitForSingleObject(cloneArmyThread, INFINITE);
    WaitForSingleObject(fleetThread, INFINITE);
    WaitForSingleObject(droidStationThread, INFINITE);
    WaitForSingleObject(tradeFederationThread, INFINITE);

    std::cout << "Конец работы" << std::endl;
}

