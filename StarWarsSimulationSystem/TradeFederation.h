#pragma once

#include "StarWarsAPI.h"
#include "Channel.h"
#include "SupportForDroidStation.h"

namespace StarWarsSystem
{
	class StarWarsObject TradeFederation
	{
	private:
		Core::Channel<SupportForDroidStation>* _channelC6; // ��� �������� ������ ������� �������
		Core::Channel<SupportForDroidStationOrder>* _channelC5; // ��� ������ ������ �� ������� �������
		int _currentAmountOfAirDefense, _currentAmountOfTanks;
		const char* _tradeFederationTag = "[Trade Federation]: ";
	public:
		TradeFederation(int amountOfAirDefense, int amountOfTanks);
		~TradeFederation();
		/**
		* ������ ����������� ������������� ����� �� ���. �������� ���
		*/
		bool IsItPossibleToSatisfyTheAirRequest(SupportForDroidStationOrder order);

		/**
		* ������ ����������� ������������� ����� �� ���. �������� �������� �������
		*/
		bool IsItPossibleToSatisfyTheGroundRequest(SupportForDroidStationOrder order);

		void Run();
	};
}
