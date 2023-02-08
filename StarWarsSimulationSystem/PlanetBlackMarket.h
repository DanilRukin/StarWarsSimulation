#pragma once

#include "GlabalNames.h"
#include "StarWarsAPI.h"
#include "PrintableObject.h"
#include "Queue.h"

namespace StarWarsSystem
{
	class StarWarsObject PlanetBlackMarket : public PrintableObject
	{
	private:
		const char* _planetBlackMarketTag = "[������� '������ �����']: ";
		Core::Queue<int>* _tanksSupplies; // �������� ������
		Core::Queue<int>* _spaceShipsSupplies; // �������� ����������� ��������/������� ���
	public:
		PlanetBlackMarket(int tanksSuppliesCount, int spaceShipsSuppliesCount);
		~PlanetBlackMarket();
		/**
		* ������� (����������) ����� ������
		*/
		void PostTanksSupply(int count);
		/**
		* ������� (����������) ����� ������� ���/����������� ��������
		*/
		void PostSpaceShipsSupply(int count);
		/**
		* ������ ����� ������
		*/
		int BuyTanksSupply();
		/**
		* ������ ����� ������� ���/����������� ��������
		*/
		int BuySpaceShipSupply();
	};
}

