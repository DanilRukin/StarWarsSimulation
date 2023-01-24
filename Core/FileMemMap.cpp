#include "FileMemMap.h"



template <class T>
Core::FileMemMap<T>::FileMemMap(std::string name)
{
	const char fileMemMapName = ("FILEMEM_" + name).c_str();
	_fileMem = OpenFileMappingA(FILE_MAP_ALL_ACCESS, false, (LPCSTR)fileMemMapName);
	if (_fileMem == nullptr)
		_fileMem = CreateFileMappingA(INVALID_HANDLE_VALUE,
			PAGE_READWRITE,
			nullptr,
			0,
			sizeof(T),
			(LPCSTR)fileMemMapName);
	if (_fileMem != nullptr)
		_data = MapViewOfFile(_fileMem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(T));
	else
		printf("\n\rAn error occured while creating an instance of FileMemMap\n\r");
}

template <class T>
void Core::FileMemMap<T>::SetData(T data)
{
	_data = data;
}

template <class T>
T Core::FileMemMap<T>::GetData()
{
	return _data;
}

template<class T>
Core::FileMemMap<T>::~FileMemMap()
{
	if (_fileMem != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_fileMem);
		_fileMem = INVALID_HANDLE_VALUE;
	}
}
