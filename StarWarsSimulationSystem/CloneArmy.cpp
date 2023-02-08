#include "CloneArmy.h"

StarWarsSystem::CloneArmy::CloneArmy(int amountOfClones, int amountOfTanks, bool isMultiThread, int waitReinforcementsTime)
	: PrintableObject(isMultiThread)
{
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC2 = new Core::Channel<Damage>(CHANNEL_C2_NAME);
	_channelC4 = new Core::Channel<int>(CHANNEL_C4_NAME);
	_channelC8 = new Core::Channel<CommandCenterOrder>(CHANNEL_C8_NAME);
	_channelC10 = new Core::Channel<int>(CHANNEL_C10_NAME);
	_amountOfClones = amountOfClones;
	_maxAmountOfClones = amountOfClones;
	_amountOfTanks = amountOfTanks;
	_maxAmountOfTanks = amountOfTanks;
	_cloneWarriorHP = 100;
	_cloneWarriorDamage = 150;
	_tankHP = 10000;
	_tankDamage = 8000;
	_waitReinforcementsTime = waitReinforcementsTime;
	Print(_armyTag, "����� ������ �������");
}

StarWarsSystem::CloneArmy::~CloneArmy()
{
	if (_channelC1 != nullptr)
	{
		delete _channelC1;
		_channelC1 = nullptr;
	}
	if (_channelC2 != nullptr)
	{
		delete _channelC2;
		_channelC2 = nullptr;
	}
	if (_channelC4 != nullptr)
	{
		delete _channelC4;
		_channelC4 = nullptr;
	}
	if (_channelC8 != nullptr)
	{
		delete _channelC8;
		_channelC8 = nullptr;
	}
}

StarWarsSystem::Damage StarWarsSystem::CloneArmy::DoDamageForDroidStation()
{
	Damage result;
	result.Sender = DamageSender::ArmyOfClones;
	int damage = _cloneWarriorDamage * _amountOfClones + _tankDamage * _amountOfTanks;
	result.DamageAmount = damage;
	return result;
}

void StarWarsSystem::CloneArmy::AcceptDamage(int damage)
{
	int damageForClones = damage / 10;
	int damageForTanks = damage - damageForClones;
	int destroyedClones = damageForClones / _cloneWarriorHP;
	int destroyedTanks = damageForTanks / _tankHP;
	_amountOfClones -= destroyedClones;
	if (_amountOfClones < 0)
		_amountOfClones = 0;
	_amountOfTanks -= destroyedTanks;
	if (_amountOfTanks < 0)
		_amountOfTanks = 0;
}

void StarWarsSystem::CloneArmy::AcceptReinforcements(int reinforcements)
{
	_amountOfTanks += reinforcements;
	if (_amountOfTanks > _maxAmountOfTanks)
		_maxAmountOfTanks = _amountOfTanks;
	return;
}

void StarWarsSystem::CloneArmy::Run()
{
	Print(_armyTag, "����� ������ ��������");
	// std::cout << _armyTag << "����� ������ ��������" << std::endl;
	CommandCenterOrder order;
	Core::ChannelResult<CommandCenterOrder> orderResult;
	Core::ChannelResult<int> responseResult;
	int responseFromDroidStation;
	Damage damage;
	std::string message;
	while (true)
	{
		// �������� ������ � ��������� � ��������� �����
		_stateReport = Report::ArmyReport(_amountOfClones, _maxAmountOfClones, _amountOfTanks, _maxAmountOfTanks);
		Print(_armyTag, "����� ������");
		_channelC1->Put(_stateReport);

		// �������� ������� �� ���������� ������
		Print(_armyTag, "�������� ������� �� ���������� ������");
		orderResult = _channelC8->Get();
		order = orderResult.Data;
		Print(_armyTag, "������ �� ���������� ������ �������");

		if (order == CommandCenterOrder::StopAttack)
		{
			Print(_armyTag, "��������� ����� - ���������������. �������� ������������...");
			responseResult = _channelC10->Get(_waitReinforcementsTime);
			if (responseResult.WaitStatus == WAIT_TIMEOUT)
			{
				Print(_armyTag, "�������� ������������ ���������� �� ����-����");
			}
			else
			{
				message = "������������ �������� � ���������� [" + std::to_string(responseResult.Data) + "]. ������������� � ����� �����.";
				Print(_armyTag, message.c_str());
				AcceptReinforcements(responseResult.Data);
			}
		}
		else
		{
			Print(_armyTag, "���������� ��������������� ��������");
			
			damage = DoDamageForDroidStation();
			message = "����� �� ������� �������, ������������ ���������� ���� = " + std::to_string(damage.DamageAmount);
			Print(_armyTag, message.c_str());
			_channelC2->Put(damage);
			
			Print(_armyTag, "�������� ������ �� ������� �������");
			responseResult = _channelC4->Get();
			responseFromDroidStation = responseResult.Data;
			message = "����� �� ������� ������� �������, ���������� ����������� ����� (" + std::to_string(responseResult.Data) + ")";
			Print(_armyTag, message.c_str());

			AcceptDamage(responseFromDroidStation);
		}
	}
}
