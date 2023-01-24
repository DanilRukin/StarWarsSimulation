#pragma once
#include <string>
#include <Windows.h>

namespace Core
{
	/**
	* ����� ��� ���������� ��������� ������ � ����� ������.
	* ������������ ������ ������ ����������.
	*/
	template <class T>
	class FileMemMap
	{
	private:
		T _data; // ������ ��� ����������
		HANDLE _fileMem; // ��������� �� ������� ������
	public:
		FileMemMap(std::string name);
		void SetData(T data);
		T GetData();
		~FileMemMap();
	};
}

