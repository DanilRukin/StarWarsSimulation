#pragma once
#include "StarWarsAPI.h"
#include "Channel.h"
#include <iostream>
#include "Report.h"
#include "GlabalNames.h"
#include "PrintableObject.h"
#include "PlanetBlackMarket.h"
#include "ReadWriteLockObject.h"

namespace StarWarsSystem
{
	/**
	* Приказы командного центра
	*/
	enum StarWarsObject CommandCenterOrder 
	{
		StartAttack, StopAttack
	};


	/**
	* Класс командного центра для удаленного управления армией клонов и космическим флотом.
	* Все наименования переменных соответствуют разработанной схеме.
	*/
	class StarWarsObject CommandCenter : public ReadWriteLockObject
	{
	private:
		/* Т.к. HANDLE канала открывается/создается по имени, то _channelC7 в этом классе будет указывать на тот же
		* объект, что и _channelC7 в классе флота.
		*/
		Core::Channel<CommandCenterOrder>* _channelC7; // канал для обмена данными с флотом
		Core::Channel<CommandCenterOrder>* _channelC8; // канал для обмена данным с армией
		Core::Channel<Report>* _channelC1; // канал для приема отчетов от армии/флота
		Core::Channel<int>* _channelC9; // канал для отправки доп. вооружений космическому флоту
		Core::Channel<int>* _channelC10; // канал для отправки доп. вооружений армии клонов
		const char* _commandCenterTag = "[Command center]: ";
		PlanetBlackMarket* _blackMarket = nullptr;

		bool IsArmyStateOk(Report report);

		bool IsFleetStateOk(Report report);
	public:
		CommandCenter(bool isMultiThread, PlanetBlackMarket* blackMarket = nullptr);

		void Run();
	};
}

