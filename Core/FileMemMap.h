#pragma once
#include <string>

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

