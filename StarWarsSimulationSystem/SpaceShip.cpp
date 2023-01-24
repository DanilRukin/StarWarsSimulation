#include "SpaceShip.h"

StarWarsSystem::SpaceShips::SpaceShip::SpaceShip(int hp, int damage)
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

int StarWarsSystem::SpaceShips::SpaceShip::GetCurrentHp()
{
	return _healthPoints;
}

int StarWarsSystem::SpaceShips::SpaceShip::DoDamage()
{
	return _damage;
}

void StarWarsSystem::SpaceShips::SpaceShip::AcceptDamage(int damage)
{
	_healthPoints -= damage;
	if (_healthPoints < 0)
		_healthPoints = 0;
	if (_healthPoints == 0)
		_status = SpaceShipStatus::Destroyed;
}

StarWarsSystem::SpaceShips::SpaceShipStatus StarWarsSystem::SpaceShips::SpaceShip::CurrentStatus()
{
	return _status;
}

