#include "CloneArmy.h"
#include <iostream>

using namespace StarWarsSystem;

int main()
{
    setlocale(LC_ALL, "ru");
    CloneArmy* army = new CloneArmy(100000, 80000, false, 30000);
    army->Run();
    return 0;
}
