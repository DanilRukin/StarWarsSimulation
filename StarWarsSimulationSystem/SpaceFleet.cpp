#include "SpaceFleet.h"
#include <iostream>

StarWarsSystem::SpaceFleet::SpaceFleet(bool isMultiThread, int waitReinforcementsTime) : PrintableObject(isMultiThread)
{
	SpaceShips::SpaceShipsFactory factory;
	_firstFlagship = factory.CreateFlagship();
	_secondFlagship = factory.CreateFlagship();
	_fighterjetsCount = 100;
	_waitReinforcementsTime = waitReinforcementsTime;
	_fighterjets = new SpaceShips::FighterJet * [_fighterjetsCount];
	for (int i = 0; i < _fighterjetsCount; i++)
	{
		_fighterjets[i] = factory.CreateFighterJet();
	}
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC2 = new Core::Channel<Damage>(CHANNEL_C2_NAME);
	_channelC3 = new Core::Channel<int>(CHANNEL_C3_NAME);
	_channelC7 = new Core::Channel<CommandCenterOrder>(CHANNEL_C7_NAME);
	_channelC9 = new Core::Channel<int>(CHANNEL_C9_NAME);
	Print(_spaceFleetTag, "космический флот создан");
}

StarWarsSystem::SpaceFleet::~SpaceFleet()
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
	if (_channelC3 != nullptr)
	{
		delete _channelC3;
		_channelC3 = nullptr;
	}
	if (_channelC7 != nullptr)
	{
		delete _channelC7;
		_channelC7 = nullptr;
	}
}

StarWarsSystem::Damage StarWarsSystem::SpaceFleet::DoDamageForDroidStation()
{
	int damage = 0;
	if (_firstFlagship->CurrentStatus() == SpaceShips::SpaceShipStatus::Ok)
		damage += _firstFlagship->DoDamage();
	if (_secondFlagship->CurrentStatus() == SpaceShips::SpaceShipStatus::Ok)
		damage += _secondFlagship->DoDamage();
	for (int i = 0; i < _fighterjetsCount; i++)
	{
		if (_fighterjets[i]->CurrentStatus() == SpaceShips::SpaceShipStatus::Ok)
			damage += _fighterjets[i]->DoDamage();
	}
	Damage result;
	result.DamageAmount = damage;
	result.Sender = DamageSender::Fleet;
	return result;
}

void StarWarsSystem::SpaceFleet::AcceptDamage(int damage)
{
	int damageForFlagships = 0.9 * damage;
	int damageForFighterjet = (damage - damageForFlagships) / _fighterjetsCount;
	if (damageForFighterjet < 1)
		damageForFighterjet = 1;
	_firstFlagship->AcceptDamage(damageForFlagships / 2);
	_secondFlagship->AcceptDamage(damageForFlagships / 2);
	for (int i = 0; i < _fighterjetsCount; i++)
	{
		if (_fighterjets[i]->CurrentStatus() == SpaceShips::SpaceShipStatus::Ok)
			_fighterjets[i]->AcceptDamage(damageForFighterjet);
	}
}

void StarWarsSystem::SpaceFleet::AcceptReinforcements(int reinforcements)
{
	SpaceShips::SpaceShipsFactory factory;
	for (int i = 0; i < _fighterjetsCount; i++)
	{
		if (reinforcements > 0)
		{
			if (_fighterjets[i]->CurrentStatus() == SpaceShips::SpaceShipStatus::Destroyed)
			{
				delete _fighterjets[i];
				_fighterjets[i] = factory.CreateFighterJet();
				reinforcements--;
			}
		}
		break;
	}
	if (reinforcements > 0)
	{
		if (_firstFlagship->CurrentStatus() == SpaceShips::SpaceShipStatus::Destroyed)
		{
			delete _firstFlagship;
			_firstFlagship = factory.CreateFlagship();
			reinforcements--;
		}			
	}
	if (reinforcements > 0)
	{
		if (_secondFlagship->CurrentStatus() == SpaceShips::SpaceShipStatus::Destroyed)
		{
			delete _secondFlagship;
			_secondFlagship = factory.CreateFlagship();
			reinforcements--;
		}
	}
	return;
}

void StarWarsSystem::SpaceFleet::Run()
{
	Print(_spaceFleetTag, "запуск");
	Report report;
	int aliveFighterjetsCount, responseFromDroidStation;
	Core::ChannelResult<CommandCenterOrder> orderResult;
	Core::ChannelResult<int> responseResult;
	CommandCenterOrder order;
	Damage damage;
	std::string message;
	while (true)
	{
		Print(_spaceFleetTag, "создание отчета о состоянии и отправка в командный центр...");
		aliveFighterjetsCount = 0;
		for (int i = 0; i < _fighterjetsCount; i++)
		{
			if (_fighterjets[i]->CurrentStatus() == SpaceShips::SpaceShipStatus::Ok)
				aliveFighterjetsCount++;
		}
		report = Report::FleetReport(aliveFighterjetsCount, _fighterjetsCount, _firstFlagship->CurrentStatus(),
			_secondFlagship->CurrentStatus());
		_channelC1->Put(report);

		Print(_spaceFleetTag, "ожидание приказа от командного центра...");
		orderResult = _channelC7->Get();
		order = orderResult.Data;
		if (order == CommandCenterOrder::StartAttack)
		{
			Print(_spaceFleetTag, "получен приказ о проведении атакующего действия");
			damage = DoDamageForDroidStation();
			message = "Нанесение удара по станции дроидов с уроном = " + std::to_string(damage.DamageAmount);
			Print(_spaceFleetTag, message.c_str());
			_channelC2->Put(damage);
			Print(_spaceFleetTag, "ожидание ответных действий от станции дроидов...");
			responseResult = _channelC3->Get();
			responseFromDroidStation = responseResult.Data;
			message = "получен урон от станции дроидов = " + std::to_string(responseFromDroidStation);
			Print(_spaceFleetTag, message.c_str());
			AcceptDamage(responseFromDroidStation);
		}
		else if (order == CommandCenterOrder::StopAttack)
		{
			Print(_spaceFleetTag, "получен приказ об отступлении... перегруппировка. Ожидание подкреплений от командного центра");
			responseResult = _channelC9->Get(_waitReinforcementsTime);
			if (responseResult.WaitStatus == WAIT_TIMEOUT)
			{
				Print(_spaceFleetTag, "ожидание подкреплений прекращено по тайм-ауту");
			}
			else
			{
				message = "получены подкрепления в количестве [" + std::to_string(responseResult.Data) + "]. Присоединение к силам флота.";
				Print(_spaceFleetTag, message.c_str());
				AcceptReinforcements(responseResult.Data);
			}
		}
		else
		{
			Print(_spaceFleetTag, "получен НЕПОНЯТНЫЙ приказ");
		}			
	}
}
