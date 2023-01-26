#include "TradeFederation.h"
#include "GlabalNames.h"
#include <iostream>

StarWarsSystem::TradeFederation::TradeFederation(int amountOfAirDefense, int amountOfTanks)
{
	if (amountOfAirDefense < 1)
		_currentAmountOfAirDefense = 1;
	else
		_currentAmountOfAirDefense = amountOfAirDefense;
	if (amountOfTanks < 1)
		_currentAmountOfTanks = 1;
	else
		_currentAmountOfTanks = amountOfTanks;
	_channelC5 = new Core::Channel<SupportForDroidStationOrder>(CHANNEL_C5_NAME);
	_channelC6 = new Core::Channel<SupportForDroidStation>(CHANNEL_C6_NAME);
	std::cout << _tradeFederationTag << "Торговая Федерация создана" << std::endl;
}

StarWarsSystem::TradeFederation::~TradeFederation()
{
	if (_channelC5 != nullptr)
	{
		delete _channelC5;
		_channelC5 = nullptr;
	}
	if (_channelC6 != nullptr)
	{
		delete _channelC6;
		_channelC6 = nullptr;
	}
}

bool StarWarsSystem::TradeFederation::IsItPossibleToSatisfyTheAirRequest(SupportForDroidStationOrder order)
{
	if (order.SupportType == SupportForDroidStationType::AirDefense)
	{
		if (order.SupportAmount <= _currentAmountOfAirDefense)
			return true;
	}
	return false;
}

bool StarWarsSystem::TradeFederation::IsItPossibleToSatisfyTheGroundRequest(SupportForDroidStationOrder order)
{
	if (order.SupportType == SupportForDroidStationType::GroundDefense)
	{
		if (order.SupportAmount <= _currentAmountOfTanks)
			return true;
	}
	return false;
}

void StarWarsSystem::TradeFederation::Run()
{
	std::cout << _tradeFederationTag << "Запуск Торговой Федерации" << std::endl;
	SupportForDroidStationOrder order;
	SupportForDroidStation support;
	Core::ChannelResult<SupportForDroidStationOrder> orderResult;
	while (true)
	{
		std::cout << _tradeFederationTag << "Ожидание запроса от станции дроидов" << std::endl;
		orderResult = _channelC5->Get();
		order = orderResult.Data;
		if (order.SupportType == SupportForDroidStationType::GroundDefense)
		{
			std::cout << _tradeFederationTag << "Получен запрос на доп. средства назменой обороны" << std::endl;
			if (IsItPossibleToSatisfyTheGroundRequest(order))
			{
				std::cout << _tradeFederationTag 
					<< "Можно удовлетворить запрос на доп. средства назменой обороны. "
					 << "Отправка..." << std::endl;
				_currentAmountOfTanks -= order.SupportAmount;
				support.SupportType = SupportForDroidStationType::GroundDefense;
				support.SupportAmount = order.SupportAmount;
				_channelC6->Put(support);
			}
			// иначе, не отвечать на запрос
		}
		else if (order.SupportType == SupportForDroidStationType::AirDefense)
		{
			std::cout << _tradeFederationTag << "Получен запрос на доп. средтва ПВО" << std::endl;
			if (IsItPossibleToSatisfyTheAirRequest(order))
			{
				std::cout << _tradeFederationTag
					<< "Можно удовлетворить запрос на доп. средства ПВО. "
					<< "Отправка..." << std::endl;
				_currentAmountOfAirDefense -= order.SupportAmount;
				support.SupportType = SupportForDroidStationType::AirDefense;
				support.SupportAmount = order.SupportAmount;
				_channelC6->Put(support);
			}
			// иначе, не отвечать на запрос
		}
		else
			std::cout << _tradeFederationTag << "Получен НЕПОНЯТНЫЙ запрос" << std::endl;
	}
}
