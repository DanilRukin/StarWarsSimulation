#include "CloneArmy.h"

StarWarsSystem::CloneArmy::CloneArmy(int amountOfClones, int amountOfTanks, bool isMultiThread) 
	: PrintableObject(isMultiThread)
{
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC2 = new Core::Channel<Damage>(CHANNEL_C2_NAME);
	_channelC4 = new Core::Channel<int>(CHANNEL_C4_NAME);
	_channelC8 = new Core::Channel<CommandCenterOrder>(CHANNEL_C8_NAME);
	_amountOfClones = amountOfClones;
	_maxAmountOfClones = amountOfClones;
	_amountOfTanks = amountOfTanks;
	_maxAmountOfTanks = amountOfTanks;
	_cloneWarriorHP = 100;
	_cloneWarriorDamage = 150;
	_tankHP = 10000;
	_tankDamage = 8000;
	Print(_armyTag, "армия клонов создана");
	// std::cout << _armyTag << "армия клонов создана" << std::endl;
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

void StarWarsSystem::CloneArmy::Run()
{
	Print(_armyTag, "армия клонов запущена");
	// std::cout << _armyTag << "армия клонов запущена" << std::endl;
	CommandCenterOrder order;
	Core::ChannelResult<CommandCenterOrder> orderResult;
	Core::ChannelResult<int> responseResult;
	int responseFromDroidStation;
	Damage damage;
	std::string message;
	while (true)
	{
		// отправка отчета о состоянии в командный центр
		_stateReport = Report::ArmyReport(_amountOfClones, _maxAmountOfClones, _amountOfTanks, _maxAmountOfTanks);
		Print(_armyTag, "отчет создан");
		// std::cout << _armyTag << "отчет создан, отправляется в командный центр" << std::endl;
		// std::cout << _armyTag << "отчет отправляется в командный центр" << std::endl;
		_channelC1->Put(_stateReport);

		// ожидание приказа от командного центра
		Print(_armyTag, "ожидание приказа от командного центра");
		// std::cout << _armyTag << "ожидание приказа от командного центра" << std::endl;
		orderResult = _channelC8->Get();
		order = orderResult.Data;
		Print(_armyTag, "приказ от командного центра получен");
		// std::cout << _armyTag << "приказ от командного центра получен" << std::endl;

		if (order == CommandCenterOrder::StopAttack)
		{
			Print(_armyTag, "остановка атаки - перегруппировка");
			// std::cout << _armyTag << "остановка атаки - перегруппировка" << std::endl;
		}
		else
		{
			Print(_armyTag, "проведение наступательного действия");
			// std::cout << _armyTag << "проведение наступательного действия" << std::endl;
			
			damage = DoDamageForDroidStation();
			message = "атака на станцию дроидов, передаваемый абсолютный урон = " + std::to_string(damage.DamageAmount);
			Print(_armyTag, message.c_str());
			/*std::cout << _armyTag << "атака на станцию дроидов, передаваемый абсолютный урон = "
				<< damage.DamageAmount
				<< std::endl;*/
			_channelC2->Put(damage);
			
			Print(_armyTag, "ожидание ответа от станции дроидов");
			// std::cout << _armyTag << "ожидание ответа от станции дроидов" << std::endl;
			responseResult = _channelC4->Get();
			responseFromDroidStation = responseResult.Data;
			message = "ответ от станции дроидов получен, применение полученного урона (" + std::to_string(responseResult.Data) + ")";
			Print(_armyTag, message.c_str());
			/*std::cout << _armyTag << "ответ от станции дроидов получен, применение полученного урона ("
				<< responseResult.Data << ")"
				<< std::endl;*/
			AcceptDamage(responseFromDroidStation);
		}
	}
}
