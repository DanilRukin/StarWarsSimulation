#pragma once
#include "Semaphore.h"
#include "FileMemMap.h"

namespace Core
{
	/**
	* Класс канала для передачи данных между потоками/процессами.
	* Виден клиентам библиотеки.
	*/
	template<class T>
	class Core_API Channel
	{
	private:
		Semaphore* _free, * _empty;
		FileMemMap<T>* _fileMem;
	public:
		Channel(std::string name);
		~Channel();
		void Put(T data);
		T Get();
	};
}

