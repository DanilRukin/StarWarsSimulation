#pragma once

/**
* ��� ������������� ������ � ���� �� ����� ��������� ��� dll � ��� ����������� ����������
*/
#ifdef STARWARSSIMULATIONSYSTEM_EXPORTS
/**
* ��� ������ ���������� ��� ������/�������, ���������� Core_API ����� ��������� � __declspec(dllexport),
* ��� ��������, ��� ��� ������/������� ����� �������� � ������� �������� dll
*/
#define StarWarsObject __declspec(dllexport) // ��� ��������� ������/������� � ������� �������� dll
#define EXTERN_STARWARS
#else
/**
* ��� ��������� �������, ��������, Semaphore.h � ���������� ���, �� ����� Core_API ����� ��������
* � __declspec(dllimport), ��� ��������, ��� ���� ����� ����� ������������ �� dll
*/
#define StarWarsObject __declspec(dllimport) // ��� ������� �� dll � ���������� ���
#define EXTERN_STARWARS extern
#endif
