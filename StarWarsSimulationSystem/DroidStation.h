#pragma once

#include "StarWarsAPI.h"
#include "Channel.h"
#include "SupportForDroidStation.h"
#include "Damage.h"
#include "PrintableObject.h"

namespace StarWarsSystem
{
	class StarWarsObject DroidStation : public PrintableObject
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
		int _droidDamage, _tankDamage, _airDefenseDamage;
		long _timeForWaitingTradeFederation;
		const char* _droidStationTag = "[Droid Station]: ";
	public:
		DroidStation(int droidsCount, int tanksCount, int airDefenseCount, bool isMultiThread, long timeForWaitingTradeFederation = INFINITE);
		~DroidStation();
		int DoDamageForArmy();
		int DoDamageForFleet();
		bool IsTanksStateOk();
		bool IsDroidsArmyStateOk();
		bool IsAirDefenseStateOk();
		void AcceptDamage(Damage damage);
		void AcceptSupport(SupportForDroidStation support);
		void ProcessDamageFromCloneArmy(Damage damage);
		void ProcessDamageFromSpaceFleet(Damage damage);
		void Run();
	};
}

