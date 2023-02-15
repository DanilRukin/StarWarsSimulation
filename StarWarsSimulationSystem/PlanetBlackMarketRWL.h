#pragma once 

#include "PlanetBlackMarket.h"
#include "StarWarsAPI.h"

namespace StarWarsSystem
{
	class StarWarsObject PlanetBlackMarketRWL : public PlanetBlackMarket
	{
	public:
		PlanetBlackMarketRWL(int tanksSuppliesCount, int spaceShipsSuppliesCount);
		/**
		* ������� (����������) ����� ������
		*/
		void PostTanksSupply(int count) override;
		/**
		* ������� (����������) ����� ������� ���/����������� ��������
		*/
		void PostSpaceShipsSupply(int count) override;
		/**
		* ������ ����� ������
		*/
		int BuyTanksSupply() override;
		/**
		* ������ ����� ������� ���/����������� ��������
		*/
		int BuySpaceShipSupply() override;
	};
}
