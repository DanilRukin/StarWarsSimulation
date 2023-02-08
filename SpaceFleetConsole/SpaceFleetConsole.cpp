#include "SpaceFleet.h"
#include <iostream>

using namespace StarWarsSystem;

int main()
{
    setlocale(LC_ALL, "ru");
    SpaceFleet* fleet = new SpaceFleet(false, 30000);
    fleet->Run();
    return 0;
}
