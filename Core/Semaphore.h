#pragma once
#include "pch.h"
#include <string>

namespace Core
{
	/**
	* Класс семафора.
	* Виден клиентам библиотеки.
	*/
	class Core_API Semaphore
	{
	private:
		HANDLE semaphore;
	public:
		Semaphore(std::string name, bool open = true);
		~Semaphore();
		/**
		* Аналог функции P().
		* Вход в семафор для ожидания
		* @param milliseconds время ожидания в миллисекундах
		*/
		void WaitOne(unsigned long milliseconds = INFINITE);

		/**
		* Аналого функции V().
		* Освобождает семафор.
		*/
		void Release();
	};
}

