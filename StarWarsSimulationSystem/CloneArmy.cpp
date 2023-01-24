#include "CloneArmy.h"

StarWarsSystem::CloneArmy::CloneArmy(int amountOfClones, int amountOfTanks)
{
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC8 = new Core::Channel<CommandCenterOrder>(CHANNEL_C8_NAME);
	_amountOfClones = amountOfClones;
	_maxAmountOfClones = amountOfClones;
	_amountOfTanks = amountOfTanks;
	_maxAmountOfTanks = amountOfTanks;
	_cloneWarriorHP = 100;
	_tankHP = 10000;
	std::cout << _armyTag << "����� ������ �������" << std::endl;
}

void StarWarsSystem::CloneArmy::Run()
{
	std::cout << _armyTag << "����� ������ ��������" << std::endl;
	CommandCenterOrder order;
	while (true)
	{
		// �������� ������ � ��������� � ��������� �����
		_stateReport = Report::ArmyReport(_amountOfClones, _maxAmountOfClones, _amountOfTanks, _maxAmountOfTanks);
		std::cout << _armyTag << "����� ������" << std::endl;
		std::cout << _armyTag << "����� ������������ � ��������� �����" << std::endl;
		_channelC1->Put(_stateReport);

		// �������� ������� �� ���������� ������
		std::cout << _armyTag << "�������� ������� �� ���������� ������" << std::endl;
		order = _channelC8->Get();
		std::cout << _armyTag << "������ �� ���������� ������ �������" << std::endl;

		if (order == CommandCenterOrder::StopAttack)
		{
			std::cout << _armyTag << "��������� �����" << std::endl;
			// TODO: stop attak
			std::cout << _armyTag << "����� �����������" << std::endl;
		}
		else
		{
			std::cout << _armyTag << "���������� ��������������� ��������" << std::endl;
			// TODO: attack droid station

			// TODO: ������� ������ �� ������� �������
			std::cout << _armyTag << "�������� ������ �� ������� �������" << std::endl;

			std::cout << _armyTag << "����� �� ������� ������� �������, ���������� ����������� �����" << std::endl;

		}
	}
}
