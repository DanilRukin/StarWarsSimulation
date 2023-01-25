#pragma once

#include "Semaphore.h"
#include "FileMemMap.h"
#include "StarWarsAPI.h"

namespace Core
{
	/**
	* Класс канала для передачи данных между потоками/процессами.
	* Виден клиентам библиотеки.
	*/
	template <class T> // ШАБЛОННЫЕ КЛАССЫ ДОЛЖНЫ СОДЕРЖАТЬ РЕАЛИЗАЦИЮ ТОЛЬКО В *.H ФАЙЛАХ
	class StarWarsObject Channel // ну, либо явно определить будущие шаблоны, например, template class Channel<int>;
	{
	private:
		Semaphore* _free, * _empty;
		FileMemMap<T>* _fileMem;
	public:
		Channel(const char* name)
		{
			std::string nameForFreeSemaphore = "CH_" + std::string(name) + "_FREE";
			_free = new Semaphore(nameForFreeSemaphore.c_str(), true);

			std::string nameForEmptySemaphore = "CH_" + std::string(name) + "_EMPTY";
			_empty = new Semaphore(nameForEmptySemaphore.c_str(), true);

			_fileMem = new FileMemMap<T>(name);
		}

		~Channel()
		{
			if (_free != nullptr)
			{
				delete _free;
				_free = nullptr;
			}
			if (_empty != nullptr)
			{
				delete _empty;
				_empty = nullptr;
			}
		}

		void Put(T data)
		{
			_free->WaitOne();
			_fileMem->SetData(data);
			_empty->Release();
		}

		T Get()
		{
			T data;
			_empty->WaitOne();
			data = _fileMem->GetData();
			_free->Release();
			return data;
		}
	};
}

