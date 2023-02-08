#include "TradeFederation.h"
#include "GlabalNames.h"
#include "PrintableObject.h"
#include <iostream>

StarWarsSystem::TradeFederation::TradeFederation(int amountOfAirDefense, int amountOfTanks, bool isMultiThread, PlanetBlackMarket* blackMarket) : PrintableObject(isMultiThread)
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
	_blackMarket = blackMarket;
	Print(_tradeFederationTag, "Торговая Федерация создана");
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
	Print(_tradeFederationTag, "Запуск Торговой Федерации");
	SupportForDroidStationOrder order;
	SupportForDroidStation support;
	Core::ChannelResult<SupportForDroidStationOrder> orderResult;
	int additionalTanks, additionalSpaceShips;
	while (true)
	{
		Print(_tradeFederationTag, "Ожидание запроса от станции дроидов");
		orderResult = _channelC5->Get();
		order = orderResult.Data;
		if (order.SupportType == SupportForDroidStationType::GroundDefense)
		{
			Print(_tradeFederationTag, "Получен запрос на доп. средства назменой обороны");
			if (IsItPossibleToSatisfyTheGroundRequest(order))
			{
				Print(_tradeFederationTag, "Можно удовлетворить запрос на доп. средства наземной обороны. Отправка...");
				_currentAmountOfTanks -= order.SupportAmount;
				support.SupportType = SupportForDroidStationType::GroundDefense;
				support.SupportAmount = order.SupportAmount;
				_channelC6->Put(support);
			}
			else
			{
				Print(_tradeFederationTag, "нельзя удовлетворить запрос на доп. средства наземной обороны. Закупка на черном рынке...");
				if (_blackMarket != nullptr)
				{
					while (!IsItPossibleToSatisfyTheGroundRequest(order)) // закупаемся до тех пор, пока не станет возможным удовлетворение запроса
					{
						additionalTanks = _blackMarket->BuyTanksSupply();
						_currentAmountOfTanks += additionalTanks;
					}
					Print(_tradeFederationTag, "Можно удовлетворить запрос на доп. средства наземной обороны. Отправка...");
					_currentAmountOfTanks -= order.SupportAmount;
					support.SupportType = SupportForDroidStationType::GroundDefense;
					support.SupportAmount = order.SupportAmount;
					_channelC6->Put(support);
				}
			}			
		}
		else if (order.SupportType == SupportForDroidStationType::AirDefense)
		{
			Print(_tradeFederationTag, "Получен запрос на доп. средтва ПВО");
			if (IsItPossibleToSatisfyTheAirRequest(order))
			{
				Print(_tradeFederationTag, "Можно удовлетворить запрос на доп. средства ПВО. Отправка...");
				_currentAmountOfAirDefense -= order.SupportAmount;
				support.SupportType = SupportForDroidStationType::AirDefense;
				support.SupportAmount = order.SupportAmount;
				_channelC6->Put(support);
			}
			else
			{
				Print(_tradeFederationTag, "нельзя удовлетворить запрос на доп. средства ПВО. Закупка на черном рынке...");
				if (_blackMarket != nullptr)
				{
					while (!IsItPossibleToSatisfyTheAirRequest(order)) // закупаемся до тех пор, пока не станет возможным удовлетворение запроса
					{
						additionalSpaceShips = _blackMarket->BuySpaceShipSupply();
						_currentAmountOfAirDefense += additionalSpaceShips;
					}
					Print(_tradeFederationTag, "Можно удовлетворить запрос на доп. средства ПВО. Отправка...");
					_currentAmountOfAirDefense -= order.SupportAmount;
					support.SupportType = SupportForDroidStationType::AirDefense;
					support.SupportAmount = order.SupportAmount;
					_channelC6->Put(support);
				}
			}
		}
		else
		{
			Print(_tradeFederationTag, "Получен НЕПОНЯТНЫЙ запрос");
		}
			
	}
}
