#include "SpaceFleet.h"
#include <iostream>

StarWarsSystem::SpaceFleet::SpaceFleet()
{
	SpaceShips::SpaceShipsFactory factory;
	_firstFlagship = factory.CreateFlagship();
	_secondFlagship = factory.CreateFlagship();
	_fighterjetsCount = 100;
	_fighterjets = new SpaceShips::FighterJet * [_fighterjetsCount];
	for (int i = 0; i < _fighterjetsCount; i++)
	{
		_fighterjets[i] = factory.CreateFighterJet();
	}
	_channelC1 = new Core::Channel<Report>(CHANNEL_C1_NAME);
	_channelC2 = new Core::Channel<Damage>(CHANNEL_C2_NAME);
	_channelC3 = new Core::Channel<int>(CHANNEL_C3_NAME);
	_channelC7 = new Core::Channel<CommandCenterOrder>(CHANNEL_C7_NAME);
	std::cout << _spaceFleetTag << "космический флот создан" << std::endl;
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

void StarWarsSystem::SpaceFleet::Run()
{
	std::cout << _spaceFleetTag << "запуск" << std::endl;
	Report report;
	int aliveFighterjetsCount, responseFromDroidStation;
	Core::ChannelResult<CommandCenterOrder> orderResult;
	Core::ChannelResult<int> responseResult;
	CommandCenterOrder order;
	Damage damage;
	while (true)
	{
		std::cout << _spaceFleetTag << "создание отчета о состоянии и отправка в командный центр..." << std::endl;
		aliveFighterjetsCount = 0;
		for (int i = 0; i < _fighterjetsCount; i++)
		{
			if (_fighterjets[i]->CurrentStatus() == SpaceShips::SpaceShipStatus::Ok)
				aliveFighterjetsCount++;
		}
		report = Report::FleetReport(aliveFighterjetsCount, _fighterjetsCount, _firstFlagship->CurrentStatus(),
			_secondFlagship->CurrentStatus());
		_channelC1->Put(report);

		std::cout << _spaceFleetTag << "ожидание приказа от командного центра..." << std::endl;
		orderResult = _channelC7->Get();
		order = orderResult.Data;
		if (order == CommandCenterOrder::StartAttack)
		{
			std::cout << _spaceFleetTag << "получен приказ о проведении атакующего действия" << std::endl;
			damage = DoDamageForDroidStation();
			std::cout << _spaceFleetTag << "Нанесение удара по станции дроидов с уроном = "
				<< damage.DamageAmount
				<< std::endl;
			_channelC2->Put(damage);
			std::cout << _spaceFleetTag << "ожидание ответных действий от станции дроидов..." << std::endl;
			responseResult = _channelC3->Get();
			responseFromDroidStation = responseResult.Data;
			std::cout << _spaceFleetTag << "получен урон от станции дроидов = "
				<< responseFromDroidStation
				<< std::endl;
			AcceptDamage(responseFromDroidStation);
		}
		else if (order == CommandCenterOrder::StopAttack)
		{
			std::cout << _spaceFleetTag << "получен приказ об отступлении... перегруппировка" << std::endl;
		}
		else
			std::cout << _spaceFleetTag << "получен НЕПОНЯТНЫЙ приказ" << std::endl;
	}
}
