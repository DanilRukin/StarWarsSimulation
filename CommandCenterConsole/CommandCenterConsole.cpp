#include <iostream>
#include "CommandCenter.h"

using namespace StarWarsSystem;

int main()
{
	setlocale(LC_ALL, "ru");
	CommandCenter* commandCenter = new CommandCenter(false);
	commandCenter->Run();
	return 0;
}
