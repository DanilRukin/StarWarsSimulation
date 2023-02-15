#pragma once

#include "GlabalNames.h"
#include "StarWarsAPI.h"
#include "PrintableObject.h"
#include "Queue.h"

namespace StarWarsSystem
{
	class StarWarsObject PlanetBlackMarket : public PrintableObject
	{
	protected:
		const char* _planetBlackMarketTag = "[������� '������ �����']: ";
		Core::Queue<int>* _tanksSupplies; // �������� ������
		Core::Queue<int>* _spaceShipsSupplies; // �������� ����������� ��������/������� ���
	public:
		PlanetBlackMarket(int tanksSuppliesCount, int spaceShipsSuppliesCount);
		~PlanetBlackMarket();
		/**
		* ������� (����������) ����� ������
		*/
		virtual void PostTanksSupply(int count);
		/**
		* ������� (����������) ����� ������� ���/����������� ��������
		*/
		virtual void PostSpaceShipsSupply(int count);
		/**
		* ������ ����� ������
		*/
		virtual int BuyTanksSupply();
		/**
		* ������ ����� ������� ���/����������� ��������
		*/
		virtual int BuySpaceShipSupply();
	};
}

