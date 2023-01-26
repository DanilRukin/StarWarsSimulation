#pragma once

#include "StarWarsAPI.h"
#include "Semaphore.h"
#include "GlabalNames.h"
#include <iostream>

namespace StarWarsSystem
{
	class StarWarsObject PrintableObject
	{
	private:
		Core::Semaphore* _printSem;
		bool _isMultiThread;
	public:
		PrintableObject(bool isMultiThread)			
		{
			_isMultiThread = isMultiThread;
			_printSem = new Core::Semaphore(SEMAPHORE_FOR_PRINT_NAME, true);
		}

		void Print(const char* tag, const char* message)
		{
			if (_isMultiThread)
			{
				_printSem->WaitOne();
				std::cout << tag << message << std::endl;
				_printSem->Release();
			}
			else
			{
				std::cout << tag << message << std::endl;
			}			
		}
	};
}
