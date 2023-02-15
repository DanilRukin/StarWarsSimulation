#include "SpaceShipsCompany.h"

StarWarsSystem::SpaceShipsComapny::SpaceShipsComapny(int id, PlanetBlackMarket* blackMarket) : ReadWriteLockObject(true)
{
	_blackMarket = blackMarket;
	_id = id;
	std::string tag = "[Space ships conpany #" + std::to_string(id) + "]: ";
	Print(tag.c_str(), "������");
}

void StarWarsSystem::SpaceShipsComapny::Run()
{
	std::string tag = "[Space ships conpany #" + std::to_string(_id) + "]: ";
	Print(tag.c_str(), "������ ������������ ������� ���/����������� ��������");
	int spaceShipsCount = 0;
	std::string message;
	while (true)
	{
		spaceShipsCount = _random.Next(1, MAX_SHIPS_COUNT);
		message = "����������� " + std::to_string(spaceShipsCount) + " ��. ������������ ����������. �������� �� ������ �����...";
		Print(tag.c_str(), message.c_str());
		_e->WaitOne(); // ���� �������� �� ���� �������
		if (NUM_R > 0 || NUM_W > 0)
		{
			WAIT_W++; // �������� ��� ���� ��������� ��������
			_e->Release();
			_w->WaitOne(); // ���� �������� �� ������
		}
		NUM_W++;
		Estafeta(); // �������� �������� - ��������! 
		_blackMarket->PostSpaceShipsSupply(spaceShipsCount);
		Print(tag.c_str(), "������ ������������ ���������� ��������� �� ������ �����.");
		_e->WaitOne(); // ���� �������� - �������� �����
		NUM_W--;
		Estafeta();
	}
}
