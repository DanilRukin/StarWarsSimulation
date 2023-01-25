#pragma once

#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	/**
	* ��� ������, ������� ���������� �������� ������ �������
	*/
	enum StarWarsObject SupportForDroidStationType
	{
		AirDefense, GroundDefense
	};
	/**
	* ������, ������� �������� ��������� ���������� ������� �������
	*/
	class StarWarsObject SupportForDroidStation
	{
	public:
		SupportForDroidStationType SupportType;
		int SupportAmount;

		SupportForDroidStation()
		{
			SupportAmount = 0;
			SupportType = SupportForDroidStationType::GroundDefense;
		}
	};
	/**
	* ���������� � ������ �� ������� ������� ��� �������� ���������
	*/
	class StarWarsObject SupportForDroidStationOrder
	{
		SupportForDroidStationType SupportType;
		int SupportAmount;
		SupportForDroidStationOrder()
		{
			SupportAmount = 0;
			SupportType = SupportForDroidStationType::GroundDefense;
		}
	};

}
