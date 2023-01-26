#include "DroidStation.h"
#include <iostream>
#include "GlabalNames.h"
#include "Channel.h"

StarWarsSystem::DroidStation::DroidStation(int droidsCount, int tanksCount, int airDefenseCount, bool isMultiThread, long timeForWaitingTradeFederation)
    : PrintableObject(isMultiThread)
{
    if (droidsCount < 1)
        _currentCountOfDroids = 1;
    else
        _currentCountOfDroids = droidsCount;
    if (tanksCount < 1)
        _currentCountOfTanks = 1;
    else
        _currentCountOfTanks = tanksCount;
    if (airDefenseCount < 1)
        _currentAirDefenseCount = 1;
    else
        _currentAirDefenseCount = airDefenseCount;
    _maxCountOfDroids = _currentCountOfDroids;
    _maxCountOfTanks = _currentCountOfTanks;
    _maxAirDefenseCount = _currentAirDefenseCount;
    _droidHp = 100;
    _droidDamage = 80;
    _tankHp = 10000;
    _tankDamage = 15000;
    _airDefenseHp = 1500;
    _airDefenseDamage = 3500;
    _timeForWaitingTradeFederation = timeForWaitingTradeFederation;
    _channelC2 = new Core::Channel<Damage>(CHANNEL_C2_NAME);
    _channelC3 = new Core::Channel<int>(CHANNEL_C3_NAME);
    _channelC4 = new Core::Channel<int>(CHANNEL_C4_NAME);
    _channelC5 = new Core::Channel<SupportForDroidStationOrder>(CHANNEL_C5_NAME);
    _channelC6 = new Core::Channel<SupportForDroidStation>(CHANNEL_C6_NAME);
    Print(_droidStationTag, "������� �������");
    //std::cout << _droidStationTag << "������� �������" << std::endl;
}

StarWarsSystem::DroidStation::~DroidStation()
{
    if (_channelC2 != nullptr)
    {
        delete _channelC2;
        _channelC2 = nullptr;
    }
    if (_channelC3 != nullptr)
    {
        delete _channelC3;
        _channelC3 = nullptr;
    }
    if (_channelC4 != nullptr)
    {
        delete _channelC4;
        _channelC4 = nullptr;
    }
    if (_channelC5 != nullptr)
    {
        delete _channelC5;
        _channelC5 = nullptr;
    }
    if (_channelC6 != nullptr)
    {
        delete _channelC6;
        _channelC6 = nullptr;
    }
}

int StarWarsSystem::DroidStation::DoDamageForArmy()
{
    int damageFromGround = _currentCountOfDroids * _droidDamage + _currentCountOfTanks * _tankDamage;
    return damageFromGround;
}

int StarWarsSystem::DroidStation::DoDamageForFleet()
{
    int damageFromAirDefense = _currentAirDefenseCount * _airDefenseDamage + _currentCountOfDroids * _droidDamage;
    return damageFromAirDefense;
}

bool StarWarsSystem::DroidStation::IsTanksStateOk()
{
    if (_currentCountOfTanks < 0.4 * _maxCountOfTanks)
        return false;
    return true;
}

bool StarWarsSystem::DroidStation::IsDroidsArmyStateOk()
{
    if (_currentCountOfDroids < 0.4 * _maxCountOfDroids)
        return false;
    return true;
}

bool StarWarsSystem::DroidStation::IsAirDefenseStateOk()
{
    if (_currentAirDefenseCount < 0.4 * _maxAirDefenseCount)
        return false;
    return true;
}

void StarWarsSystem::DroidStation::AcceptDamage(Damage damage)
{
    if (damage.Sender == DamageSender::ArmyOfClones)
    {
        int destroyedTanks = damage.DamageAmount / _tankHp;
        _currentCountOfTanks -= destroyedTanks;
        if (_currentCountOfTanks < 0)
            _currentCountOfTanks = 0;
    }
    else if (damage.Sender == DamageSender::Fleet)
    {
        int destroyedAirDefense = damage.DamageAmount / _airDefenseHp;
        _currentAirDefenseCount -= destroyedAirDefense;
        if (_currentAirDefenseCount < 0)
            _currentAirDefenseCount = 0;
    }
}

void StarWarsSystem::DroidStation::AcceptSupport(SupportForDroidStation support)
{
    if (support.SupportType = SupportForDroidStationType::GroundDefense)
    {
        _currentCountOfTanks += support.SupportAmount;
        if (_currentCountOfTanks > _maxCountOfTanks)
            _maxCountOfTanks = _currentCountOfTanks;
    }
    else if (support.SupportType == SupportForDroidStationType::AirDefense)
    {
        _currentAirDefenseCount += support.SupportAmount;
        if (_currentAirDefenseCount > _maxAirDefenseCount)
            _maxAirDefenseCount = _currentAirDefenseCount;
    }
}

void StarWarsSystem::DroidStation::ProcessDamageFromCloneArmy(Damage damage)
{
    SupportForDroidStation support;
    Core::ChannelResult<SupportForDroidStation> supportChannelResult;
    SupportForDroidStationOrder order;
    int damageForFleet;
    int additionalAmoutnOfAirDefense;
    std::string message;
    message = "������� ����������� ����, ���������� ����: " + std::to_string(damage.DamageAmount);
    Print(_droidStationTag, message.c_str());
    /*std::cout << _droidStationTag << "������� ����������� ����, ���������� ����: "
        << damage.DamageAmount
        << std::endl;*/
    AcceptDamage(damage);
    damageForFleet = DoDamageForFleet();
    message = "�������� ���� ������������ �����, ����: " + std::to_string(damageForFleet);
    Print(_droidStationTag, message.c_str());
    /*std::cout << _droidStationTag << "�������� ���� ������������ �����, ����: "
        << damageForFleet
        << std::endl;*/
    _channelC3->Put(damageForFleet);
    if (IsAirDefenseStateOk())
    {
        Print(_droidStationTag, "������ ��������� ������� ���...��������� �������");
        /*std::cout << _droidStationTag << "������ ��������� ������� ���..."
            << "��������� �������"
            << std::endl;*/
    }
    else
    {
        Print(_droidStationTag, "������ ��������� ������� ���...��������� ������");
        /*std::cout << _droidStationTag << "������ ��������� ������� ���..."
            << "��������� ������"
            << std::endl;*/
        additionalAmoutnOfAirDefense = (_maxAirDefenseCount - _currentAirDefenseCount) / 2;
        if (additionalAmoutnOfAirDefense == 0)
            additionalAmoutnOfAirDefense = 1;
        message = "�������� ������ �� ���. �������� ��� � ����������: " + std::to_string(additionalAmoutnOfAirDefense) + " ����";
        Print(_droidStationTag, message.c_str());
        /*std::cout << _droidStationTag << "�������� ������ �� ���. �������� ��� � ����������: "
            << additionalAmoutnOfAirDefense << " ����"
            << std::endl;*/
        order.SupportAmount = additionalAmoutnOfAirDefense;
        order.SupportType = SupportForDroidStationType::AirDefense;

        _channelC5->Put(order);

        message = "�������� ������ �� ������� ������� � �������: " + std::to_string(_timeForWaitingTradeFederation) + " ��";
        Print(_droidStationTag, message.c_str());
        /*std::cout << _droidStationTag << "�������� ������ �� ������� ������� � �������: "
            << _timeForWaitingTradeFederation << " ��"
            << std::endl;*/

        supportChannelResult = _channelC6->Get(_timeForWaitingTradeFederation);
        if (supportChannelResult.WaitStatus == WAIT_TIMEOUT)
        {
            Print(_droidStationTag, "�������� ������ ���������� �� ���� ����");
            // std::cout << _droidStationTag << "�������� ������ ���������� �� ���� ����" << std::endl;
            return;
        }
        else
        {
            support = supportChannelResult.Data;
            message = "�������� ���. �������� ��� � ����������: " + std::to_string(support.SupportAmount) + " ����";
            Print(_droidStationTag, message.c_str());
            /*std::cout << _droidStationTag << "�������� ���. �������� ��� � ����������: "
                << support.SupportAmount << " ����"
                << std::endl;*/
            AcceptSupport(support);
        }
    }
}

void StarWarsSystem::DroidStation::ProcessDamageFromSpaceFleet(Damage damage)
{
    SupportForDroidStation support;
    Core::ChannelResult<SupportForDroidStation> supportChannelResult;
    SupportForDroidStationOrder order;
    int damageForArmy;
    int additionalAmoutnOfTanks;
    std::string message;
    message = "������� ����� ������, ���������� ����: " + std::to_string(damage.DamageAmount);
    Print(_droidStationTag, message.c_str());
    /*std::cout << _droidStationTag << "������� ����� ������, ���������� ����: "
        << damage.DamageAmount
        << std::endl;*/
    AcceptDamage(damage);
    damageForArmy = DoDamageForArmy();
    message = "�������� ���� �� ����� ������, ����: " + std::to_string(damageForArmy);
    Print(_droidStationTag, message.c_str());
    /*std::cout << _droidStationTag << "�������� ���� �� ����� ������, ����: "
        << damageForArmy
        << std::endl;*/
    _channelC4->Put(damageForArmy);
    if (IsTanksStateOk())
    {
        Print(_droidStationTag, "������ ��������� ������� �������� �������...��������� �������");
        /*std::cout << _droidStationTag << "������ ��������� ������� �������� �������..."
            << "��������� �������"
            << std::endl;*/
    }
    else
    {
        Print(_droidStationTag, "������ ��������� ������� �������� �������...��������� ������");
        /*std::cout << _droidStationTag << "������ ��������� ������� �������� �������..."
            << "��������� ������"
            << std::endl;*/
        additionalAmoutnOfTanks = (_maxCountOfTanks - _currentCountOfTanks) / 2;
        if (additionalAmoutnOfTanks == 0)
            additionalAmoutnOfTanks = 1;
        message = "�������� ������ �� ���. �������� �������� ������� � ����������: " + std::to_string(additionalAmoutnOfTanks) + " ����";
        Print(_droidStationTag, message.c_str());
        /*std::cout << _droidStationTag << "�������� ������ �� ���. �������� �������� ������� � ����������: "
            << additionalAmoutnOfTanks << " ����"
            << std::endl;*/
        order.SupportAmount = additionalAmoutnOfTanks;
        order.SupportType = SupportForDroidStationType::GroundDefense;

        _channelC5->Put(order);

        message = "�������� ������ �� ������� ������� � �������: " + std::to_string(_timeForWaitingTradeFederation) + " ��";
        Print(_droidStationTag, message.c_str());
        /*std::cout << _droidStationTag << "�������� ������ �� ������� ������� � �������: "
            << _timeForWaitingTradeFederation << " ��"
            << std::endl;*/

        supportChannelResult = _channelC6->Get(_timeForWaitingTradeFederation);
        if (supportChannelResult.WaitStatus == WAIT_TIMEOUT)
        {
            Print(_droidStationTag, "�������� ������ ���������� �� ���� ����");
            std::cout << _droidStationTag << "�������� ������ ���������� �� ���� ����" << std::endl;
            return;
        }
        else
        {           
            support = supportChannelResult.Data;
            message = "�������� ���. �������� �������� ������� � ����������: " + std::to_string(support.SupportAmount) + " ����";
            Print(_droidStationTag, message.c_str());
            /*std::cout << _droidStationTag << "�������� ���. �������� �������� ������� � ����������: "
                << support.SupportAmount << " ����"
                << std::endl;*/
            AcceptSupport(support);
        }
    }
}

void StarWarsSystem::DroidStation::Run()
{
    Print(_droidStationTag, "������� ��������");
    // std::cout << _droidStationTag << "������� ��������" << std::endl;
    Damage damage;
    Core::ChannelResult<Damage> damageChannelResult;
    SupportForDroidStationOrder order;
    
    int damageForArmy, damageForFleet;
    int additionalAmoutnOfTanks, additionalAmountOfAirDefense;
    while (true)
    {
        Print(_droidStationTag, "�������� ����� �� ����� ��� �����...");
        // std::cout << _droidStationTag << "�������� ����� �� ����� ��� �����..." << std::endl;
        damageChannelResult = _channelC2->Get();
        damage = damageChannelResult.Data;
        if (damage.Sender == DamageSender::ArmyOfClones)
        {
            ProcessDamageFromCloneArmy(damage);           
        }
        else
        {
            ProcessDamageFromSpaceFleet(damage);
        }
    }
}
