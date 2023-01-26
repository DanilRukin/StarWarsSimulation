#include "TradeFederation.h"
#include <iostream>

using namespace StarWarsSystem;

int main()
{
    setlocale(LC_ALL, "ru");
    TradeFederation* federation = new TradeFederation(1000000, 1000000, false);
    federation->Run();
    return 0;
}
