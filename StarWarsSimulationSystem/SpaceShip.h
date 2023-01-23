#pragma once
#include <exception>
#include <string>

namespace StarWarsSystem
{
	namespace SpaceShips
	{
		enum SpaceShipStatus
		{
			Ok, Destroyed
		};

		class SpaceShip
		{
		protected:
			int _healthPoints;
			int _maxHealthPoints;
			int _damage;
			SpaceShipStatus _status;

		public:
			SpaceShip(int hp, int damage)
			{
				if (hp < 1)
					throw std::exception(("HP is very small { " + std::to_string(hp) + " }").c_str());
				if (damage < 1)
					throw std::exception(("Damage is very small { " + std::to_string(damage) + " }").c_str());
				_healthPoints = hp;
				_maxHealthPoints = hp;
				_damage = damage;
				_status = SpaceShipStatus::Ok;
			}

			int GetCurrentHp()
			{
				return _healthPoints;
			}

			virtual int DoDamage()
			{
				return _damage;
			}

			virtual void AcceptDamage(int damage)
			{
				_healthPoints -= damage;
				if (_healthPoints < 0)
					_healthPoints = 0;
				if (_healthPoints == 0)
					_status = SpaceShipStatus::Destroyed;
			}

			SpaceShipStatus CurrentStatus()
			{
				return _status;
			}
		};
	}
}

