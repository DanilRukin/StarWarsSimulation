#pragma once
#include "starwarspch.h"
#include "Channel.h"

namespace StarWarsSystem
{
	/**
	* ������� ���������� ������
	*/
	enum StarWarsObject CommandCenterOrder
	{
		StartAttack, StopAttack
	};


	/**
	* ����� ���������� ������ ��� ���������� ���������� ������ ������ � ����������� ������.
	* ��� ������������ ���������� ������������� ������������� �����.
	*/
	class StarWarsObject CommandCenter
	{
	private:
		/* �.�. HANDLE ������ �����������/��������� �� �����, �� _channelC7 � ���� ������ ����� ��������� �� ��� ��
		* ������, ��� � _channelC7 � ������ �����.
		*/
		Core::Channel<CommandCenterOrder>* _channelC7; // ����� ��� ������ ������� � ������
		Core::Channel<CommandCenterOrder>* _channelC8; // ����� ��� ������ ������ � ������
		Core::Channel<CommandCenterOrder>* _channelC1; // ����� ��� ������ ������� �� �����/�����
	};
}

