#pragma once
#include "CoreAPI.h"
#include <Windows.h>
#include <string>

namespace Core
{
	/**
	* ����� ��������.
	* ����� �������� ����������.
	*/
	class Core_API Semaphore
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
		* ������ ������� P().
		* ���� � ������� ��� ��������
		* @param milliseconds ����� �������� � �������������
		*/
		void WaitOne(unsigned long milliseconds = INFINITE)
		{
			WaitForSingleObject(semaphore, milliseconds);
		}

		/**
		* ������� ������� V().
		* ����������� �������.
		*/
		void Release()
		{
			ReleaseSemaphore(semaphore, 1, 0);
		}
	};
}

