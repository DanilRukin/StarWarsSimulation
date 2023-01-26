#pragma once

#include "Semaphore.h"
#include "FileMemMap.h"
#include "StarWarsAPI.h"

namespace Core
{
	/**
	* Контрейнер для результата со статусом ожидания
	*/
	template <class T>
	class StarWarsObject ChannelResult
	{
	public:
		T Data;
		DWORD WaitStatus;
	};
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

		void Put(T data, long waitForMilliseconds = INFINITE)
		{
			_free->WaitOne(waitForMilliseconds);
			_fileMem->SetData(data);
			_empty->Release();
		}

		ChannelResult<T> Get(long waitForMilliseconds = INFINITE)
		{
			T data;
			ChannelResult<T> result;
			DWORD waitStatus = _empty->WaitOne(waitForMilliseconds);
			if (waitStatus == WAIT_TIMEOUT)
			{
				result.WaitStatus = waitStatus;
				return result;
			}
			data = _fileMem->GetData();
			_free->Release();  // ReleaseSemaphore(free, 1, 0);
			result.WaitStatus = waitStatus;
			result.Data = data;
			return result;
		}
	};
}

