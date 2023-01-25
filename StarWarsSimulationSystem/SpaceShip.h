#pragma once
#include <exception>
#include <string>
#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	namespace SpaceShips
	{
		enum StarWarsObject SpaceShipStatus
		{
			Ok, Destroyed
		};

		class StarWarsObject SpaceShip
		{
		protected:
			int _healthPoints;
			int _maxHealthPoints;
			int _damage;
			SpaceShipStatus _status;

		public:
			SpaceShip(int hp, int damage);

			int GetCurrentHp();

			virtual int DoDamage();

			virtual void AcceptDamage(int damage);

			SpaceShipStatus CurrentStatus();
		};
	}
}

