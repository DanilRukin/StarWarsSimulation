#pragma once
#include <string>
#include <Windows.h>

namespace Core
{
	/**
	* Класс для сохранения некоторых данных в общей памяти.
	* Используется только внутри библиотеки.
	*/
	template <class T>
	class FileMemMap
	{
	private:
		T _data; // данные для сохранения
		HANDLE _fileMem; // указатель на область памяти
	public:
		FileMemMap(std::string name);
		void SetData(T data);
		T GetData();
		~FileMemMap();
	};
}

