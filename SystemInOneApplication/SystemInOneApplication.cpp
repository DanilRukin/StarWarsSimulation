#include <iostream>
#include "CloneArmy.h"
#include "CommandCenter.h"
#include "SpaceFleet.h"

using namespace StarWarsSystem;

CloneArmy* army;
CommandCenter* commandCenter;
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

int main()
{
    setlocale(LC_ALL, "ru");
    HANDLE commandCenterThread, cloneArmyThread;
    DWORD commandCenterThreadId, cloneArmyThreadId;
    army = new CloneArmy(100, 10);
    commandCenter = new CommandCenter();
    std::cout << "Запуск потоков" << std::endl;
    cloneArmyThread = CreateThread(nullptr, 0, ArmyRun, (void*)nullptr, 0, &cloneArmyThreadId);
    commandCenterThread = CreateThread(nullptr, 0, CommandCenterRun, (void*)nullptr, 0, &commandCenterThreadId);
    std::cout << "Потоки запущены" << std::endl;
    WaitForSingleObject(commandCenterThread, INFINITE);
    WaitForSingleObject(cloneArmyThread, INFINITE);

    std::cout << "Конец работы" << std::endl;
}

