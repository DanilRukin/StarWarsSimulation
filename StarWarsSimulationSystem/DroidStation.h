#pragma once

#include "StarWarsAPI.h"
#include "Channel.h"
#include "SupportForDroidStation.h"
#include "Damage.h"

namespace StarWarsSystem
{
	class StarWarsObject DroidStation
	{
	private:
		Core::Channel<Damage>* _channelC2; // принимать урон от армии или флота
		Core::Channel<int>* _channelC3; // отвечать флоту
		Core::Channel<int>* _channelC4; // отвечать армии
		Core::Channel<SupportForDroidStationOrder>* _channelC5; // для отправки заказа о помощи в Торговую Федерацию
		Core::Channel<SupportForDroidStation>* _channelC6; // для приема помощи от Торговой Федерации
		int _currentCountOfDroids, _maxCountOfDroids;
		int _currentCountOfTanks, _maxCountOfTanks;
		int _currentAirDefenseCount, _maxAirDefenseCount;
		int _droidHp, _tankHp, _airDefenseHp;
	public:
		DroidStation(int droidsCount, int tanksCount, int airDefenseCount);
		~DroidStation();
		int DoDamageForArmy();
		int DoDamageForFleet();
		bool IsTanksStateOk();
		bool IsDroidsArmyStateOk();
		bool IsAirDefenseStateOk();
		void Run();
	};
}

