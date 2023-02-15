#pragma once

#include "StarWarsAPI.h"
#include <Windows.h>

namespace StarWarsSystem
{
	extern StarWarsObject const char* CHANNEL_C1_NAME;
	extern StarWarsObject const char* CHANNEL_C2_NAME;
	extern StarWarsObject const char* CHANNEL_C3_NAME;
	extern StarWarsObject const char* CHANNEL_C4_NAME;
	extern StarWarsObject const char* CHANNEL_C5_NAME;
	extern StarWarsObject const char* CHANNEL_C6_NAME;
	extern StarWarsObject const char* CHANNEL_C7_NAME;
	extern StarWarsObject const char* CHANNEL_C8_NAME;
	extern StarWarsObject const char* CHANNEL_C9_NAME;
	extern StarWarsObject const char* CHANNEL_C10_NAME;

	extern StarWarsObject const char* SEMAPHORE_FOR_PRINT_NAME;

	extern StarWarsObject CONDITION_VARIABLE TanksBufferNotEmpty;
	extern StarWarsObject CONDITION_VARIABLE TanksBufferNotFull;
	extern StarWarsObject CRITICAL_SECTION TanksBufferLock;

	extern StarWarsObject CONDITION_VARIABLE SpaceShipsBufferNotEmpty;
	extern StarWarsObject CONDITION_VARIABLE SpaceShipsBufferNotFull;
	extern StarWarsObject CRITICAL_SECTION SpaceShipsBufferLock;

	extern void StarWarsObject InitConditionVariablesAndCriticalSection();

	extern StarWarsObject const char* WRITE_SEMAPHORE_NAME;
	extern StarWarsObject const char* READ_SEMAPHORE_NAME;
	extern StarWarsObject const char* E_SEMAPHORE_NAME;
	extern StarWarsObject int NUM_R;
	extern StarWarsObject int NUM_W;
	extern StarWarsObject int WAIT_R;
	extern StarWarsObject int WAIT_W;
}
