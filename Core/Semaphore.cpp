#include "pch.h"
#include "Semaphore.h"


void Core::Semaphore::WaitOne(unsigned long milliseconds)
{
	WaitForSingleObject(semaphore, milliseconds);
}

void Core::Semaphore::Release()
{
	ReleaseSemaphore(semaphore, 1, 0);
}

Core::Semaphore::Semaphore(std::string name, bool open)
{
	name = "SEM_" + name;
	const char* semName = name.c_str();
	semaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, true, (LPCSTR)semName);
	if (semaphore == NULL)
		semaphore = CreateSemaphoreA(NULL, open, 1, (LPCSTR)semName);
}

Core::Semaphore::~Semaphore()
{
	if (semaphore != INVALID_HANDLE_VALUE)
	{
		CloseHandle(semaphore);
		semaphore = INVALID_HANDLE_VALUE;
	}
}