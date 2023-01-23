#include "pch.h"
#include "Channel.h"


template<class T>
Core::Channel<T>::Channel(std::string name)
{
	std::string nameForFreeSemaphore = "CH_" + name + "_FREE";
	_free = new Semaphore(nameForFreeSemaphore, true);

	std::string nameForEmptySemaphore = "CH_" + name + "_EMPTY";
	_empty = new Semaphore(nameForEmptySemaphore, true);

	_fileMem = new FileMemMap<T>(name);
}

template<class T>
Core::Channel<T>::~Channel()
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

template<class T>
void Core::Channel<T>::Put(T data)
{
	_free->WaitOne();
	_fileMem->SetData(data);
	_empty->Release();
}

template<class T>
T Core::Channel<T>::Get()
{
	T data;
	_empty->WaitOne();
	data = _fileMem->GetData();
	_free->Release();
	return data;
}