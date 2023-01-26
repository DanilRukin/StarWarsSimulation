#pragma once

#include "StarWarsAPI.h"
#include <Windows.h>
#include <string>

namespace Core
{
	/**
	* Класс семафора.
	* Виден клиентам библиотеки.
	*/
	class StarWarsObject Semaphore
	{
	private:
		HANDLE semaphore;
	public:
		Semaphore(const char* name, bool open = true)
		{
			std::string semStrName = "SEM_" + std::string(name);
			const char* semName = semStrName.c_str();
			semaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, true, (LPCSTR)semName);
			if (semaphore == NULL)
				semaphore = CreateSemaphoreA(NULL, open, 1, (LPCSTR)semName);
		}
		~Semaphore()
		{
			if (semaphore != INVALID_HANDLE_VALUE)
			{
				CloseHandle(semaphore);
				semaphore = INVALID_HANDLE_VALUE;
			}
		}
		/**
		* Аналог функции P().
		* Вход в семафор для ожидания
		* @param milliseconds время ожидания в миллисекундах
		*/
		DWORD WINAPI WaitOne(unsigned long milliseconds = INFINITE)
		{
			return WaitForSingleObject(semaphore, milliseconds);
		}

		/**
		* Аналого функции V().
		* Освобождает семафор.
		*/
		void Release()
		{
			ReleaseSemaphore(semaphore, 1, 0);
		}
	};
}


