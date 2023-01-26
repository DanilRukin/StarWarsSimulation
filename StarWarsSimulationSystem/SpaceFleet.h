#pragma once
#include "StarWarsAPI.h"
#include "FighterJet.h"
#include "Flagship.h"
#include "Channel.h"
#include "SpaceShipsFactory.h"
#include "CommandCenter.h"
#include "Report.h"
#include "GlabalNames.h"
#include "Damage.h"
#include "PrintableObject.h"

namespace StarWarsSystem
{
	class StarWarsObject SpaceFleet : public PrintableObject
	{
	private:
		int _fighterjetsCount;
		SpaceShips::Flagship* _firstFlagship, * _secondFlagship;
		SpaceShips::FighterJet** _fighterjets;
		
		Core::Channel<Report>* _channelC1; // ����� ��� ������ ������� �� �����/�����;
		Core::Channel<Damage>* _channelC2; // ��� ����� �� ������� �������
		Core::Channel<int>* _channelC3; // ����� ����� �� ������� �������
		Core::Channel<CommandCenterOrder>* _channelC7; // ��� ������ �������� �� ���������� ������

		const char* _spaceFleetTag = "[Space Fleet]: ";
	public:
		
		SpaceFleet(bool isMultiThread);
		~SpaceFleet();
		Damage DoDamageForDroidStation();
		void AcceptDamage(int damage);
		void Run();
	};
}

