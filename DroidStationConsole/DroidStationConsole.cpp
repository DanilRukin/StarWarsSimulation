#include "DroidStation.h"
#include <iostream>

using namespace StarWarsSystem;

int main()
{
    setlocale(LC_ALL, "ru");
    DroidStation* station = new DroidStation(10000, 10000, 10000, false, 30000);
    station->Run();
    return 0;
}
