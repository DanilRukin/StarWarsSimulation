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
	public:
		TradeFederation(int amountOfAirDefense, int amountOfTanks);
		~TradeFederation();
		/**
		* ������ ����������� ������������� ����� �� ���. �������� ���
		*/
		bool IsItPossibleToSatisfyTheAirRequest();

		/**
		* ������ ����������� ������������� ����� �� ���. �������� �������� �������
		*/
		bool IsItPossibleToSatisfyTheGroundRequest();

		void Run();
	};
}
