#pragma once
#include "pch.h"
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
		Semaphore(std::string name, bool open = true);
		~Semaphore();
		/**
		* ������ ������� P().
		* ���� � ������� ��� ��������
		* @param milliseconds ����� �������� � �������������
		*/
		void WaitOne(unsigned long milliseconds = INFINITE);

		/**
		* ������� ������� V().
		* ����������� �������.
		*/
		void Release();
	};
}

