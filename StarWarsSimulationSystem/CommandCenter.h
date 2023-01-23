#pragma once
#include "starwarspch.h"
#include "Channel.h"

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
	class StarWarsObject CommandCenter
	{
	private:
		/* Т.к. HANDLE канала открывается/создается по имени, то _channelC7 в этом классе будет указывать на тот же
		* объект, что и _channelC7 в классе флота.
		*/
		Core::Channel<CommandCenterOrder>* _channelC7; // канал для обмена данными с флотом
		Core::Channel<CommandCenterOrder>* _channelC8; // канал для обмена данным с армией
		Core::Channel<CommandCenterOrder>* _channelC1; // канал для приема отчетов от армии/флота
	};
}

