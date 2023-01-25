#pragma once


#include <string>
#include <Windows.h>
#include "StarWarsAPI.h"

namespace Core
{
	/**
	* Класс для сохранения некоторых данных в общей памяти.
	* Используется только внутри библиотеки.
	*/
	template <class T>
	class StarWarsObject FileMemMap
	{
	private:
		void* _data; // данные для сохранения
		HANDLE _fileMem; // указатель на область памяти
		unsigned int _sizeInBytes;
	public:
		FileMemMap(const char* name, unsigned int sizeInBytes = 4096)
		{
			_sizeInBytes = sizeInBytes;
			std::string fileMemStrName = "FILEMEM_" + std::string(name);
			const char* fileMemMapName = fileMemStrName.c_str();
			_fileMem = OpenFileMappingA(FILE_MAP_ALL_ACCESS, false, (LPCSTR)fileMemMapName);
			if (_fileMem == nullptr)
				_fileMem = CreateFileMappingA(INVALID_HANDLE_VALUE,
					nullptr,
					PAGE_READWRITE,
					0,
					_sizeInBytes,
					(LPCSTR)fileMemMapName);
			if (_fileMem != nullptr)
				_data = MapViewOfFile(_fileMem, FILE_MAP_ALL_ACCESS, 0, 0, _sizeInBytes);
			else
				printf("\n\rAn error occured while creating an instance of FileMemMap\n\r");
		}
		void SetData(T data)
		{
			*((T*)_data) = data;
		}
		T GetData()
		{
			return *((T*)_data);
		}
		~FileMemMap()
		{
			if (_fileMem != INVALID_HANDLE_VALUE)
			{
				CloseHandle(_fileMem);
				_fileMem = INVALID_HANDLE_VALUE;
			}
		}
	};
}
