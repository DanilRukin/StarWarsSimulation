#include "Flagship.h"

StarWarsSystem::SpaceShips::Flagship::Flagship(int hp, int damage, int energyShieldHealthPoints) : SpaceShip(hp, damage)
{
	_energyShieldHealthPoints = energyShieldHealthPoints;
}

void StarWarsSystem::SpaceShips::Flagship::AcceptDamage(int damage)
{
	if (_status == SpaceShipStatus::Destroyed)
		return;
	int realDamage = 0;
	if (_energyShieldHealthPoints > damage)
		_energyShieldHealthPoints -= damage;
	else
		realDamage = damage - _energyShieldHealthPoints;
	if (_energyShieldHealthPoints < 0)
		_energyShieldHealthPoints = 0;
	_healthPoints -= realDamage;
	if (_healthPoints <= 0)
		_status = SpaceShipStatus::Destroyed;
}

int StarWarsSystem::SpaceShips::Flagship::DoDamage()
{
	if (_healthPoints >(_maxHealthPoints / 2))
		return _damage * 2;
	else
		return _damage;
}
