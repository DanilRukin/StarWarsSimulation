#include "GlabalNames.h"

const char* StarWarsSystem::CHANNEL_C1_NAME = "channel_c1";
const char* StarWarsSystem::CHANNEL_C2_NAME = "channel_c2";
const char* StarWarsSystem::CHANNEL_C3_NAME = "channel_c3";
const char* StarWarsSystem::CHANNEL_C4_NAME = "channel_c3";
const char* StarWarsSystem::CHANNEL_C5_NAME = "channel_c5";
const char* StarWarsSystem::CHANNEL_C6_NAME = "channel_c6";
const char* StarWarsSystem::CHANNEL_C7_NAME = "channel_c7";
const char* StarWarsSystem::CHANNEL_C8_NAME = "channel_c8";
const char* StarWarsSystem::CHANNEL_C9_NAME = "channel_c9";
const char* StarWarsSystem::CHANNEL_C10_NAME = "channel_c10";

const char* StarWarsSystem::SEMAPHORE_FOR_PRINT_NAME = "print_to_console";

CRITICAL_SECTION StarWarsSystem::TanksBufferLock;
CONDITION_VARIABLE StarWarsSystem::TanksBufferNotEmpty;
CONDITION_VARIABLE StarWarsSystem::TanksBufferNotFull;

CRITICAL_SECTION StarWarsSystem::SpaceShipsBufferLock;
CONDITION_VARIABLE StarWarsSystem::SpaceShipsBufferNotEmpty;
CONDITION_VARIABLE StarWarsSystem::SpaceShipsBufferNotFull;



void StarWarsSystem::InitConditionVariablesAndCriticalSection()
{
	InitializeConditionVariable(&TanksBufferNotEmpty);
	InitializeConditionVariable(&TanksBufferNotFull);
	InitializeCriticalSection(&TanksBufferLock);

	InitializeConditionVariable(&SpaceShipsBufferNotEmpty);
	InitializeConditionVariable(&SpaceShipsBufferNotFull);
	InitializeCriticalSection(&SpaceShipsBufferLock);
}
