#pragma once

#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	/**
	* Вид помощи, которую необходимо получить стации дроидов
	*/
	enum StarWarsObject SupportForDroidStationType
	{
		AirDefense, GroundDefense
	};
	/**
	* Помощь, которую Торговая Федерация отправляет станции дроидов
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
	* Требование о помощи от станции дроидов для Торговой Федерации
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
