#pragma once

#include "StarWarsAPI.h"
#include "Channel.h"
#include "SupportForDroidStation.h"
#include "PrintableObject.h"
#include "PlanetBlackMarket.h"
#include "ReadWriteLockObject.h"


namespace StarWarsSystem
{
	class StarWarsObject TradeFederation : public ReadWriteLockObject
	{
	private:
		Core::Channel<SupportForDroidStation>* _channelC6; // для отправки помощи станции дроидов
		Core::Channel<SupportForDroidStationOrder>* _channelC5; // для приема заказа от станции дроидов
		int _currentAmountOfAirDefense, _currentAmountOfTanks;
		const char* _tradeFederationTag = "[Trade Federation]: ";
		PlanetBlackMarket* _blackMarket = nullptr;
	public:
		TradeFederation(int amountOfAirDefense, int amountOfTanks, bool isMultiThread, PlanetBlackMarket* blackMarket = nullptr);
		~TradeFederation();
		/**
		* Оценка возможности удовлетворить заказ на доп. средства ПВО
		*/
		bool IsItPossibleToSatisfyTheAirRequest(SupportForDroidStationOrder order);

		/**
		* Оценка возможности удовлетворить заказ на доп. средства наземной обороны
		*/
		bool IsItPossibleToSatisfyTheGroundRequest(SupportForDroidStationOrder order);
		void Run();
	};
}
