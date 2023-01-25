#pragma once

#include "StarWarsAPI.h"
#include "Channel.h"
#include "SupportForDroidStation.h"

namespace StarWarsSystem
{
	class StarWarsObject TradeFederation
	{
	private:
		Core::Channel<SupportForDroidStation>* _channelC6; // для отправки помощи станции дроидов
		Core::Channel<SupportForDroidStationOrder>* _channelC5; // для приема заказа от станции дроидов
		int _currentAmountOfAirDefense, _currentAmountOfTanks;
	public:
		TradeFederation(int amountOfAirDefense, int amountOfTanks);
		~TradeFederation();
		/**
		* Оценка возможности удовлетворить заказ на доп. средства ПВО
		*/
		bool IsItPossibleToSatisfyTheAirRequest();

		/**
		* Оценка возможности удовлетворить заказ на доп. средства наземной обороны
		*/
		bool IsItPossibleToSatisfyTheGroundRequest();

		void Run();
	};
}
