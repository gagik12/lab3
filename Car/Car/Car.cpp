#include "stdafx.h"
#include "Car.h"

bool CCar::IsNeutralGear() const
{
	return m_selectGear == Gear::NEUTRAL_GEAR;
}

int CCar::GetGear() const
{
	return static_cast<int>(m_selectGear);
}

int CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::IsTurnOnEngine() const
{
	return m_isOn;
}

bool CCar::TurnOnEngine()
{
	return !m_isOn ? m_isOn = true : false;
}

bool CCar::TurnOffEngine()
{
	bool isTurnOffEngine = false;
	if (IsNeutralGear() && m_isOn && (m_speed == 0))
	{
		m_isOn = false;
		isTurnOffEngine = true; 
	}
	return isTurnOffEngine;
}

bool CCar::CheckGear(int gear) const
{
	return ((static_cast<Gear>(gear) == Gear::REVERSE) && (m_speed == 0)) ||
		((m_selectGear == Gear::REVERSE) && (static_cast<Gear>(gear) == Gear::FIRST_GEAR) && (m_speed == 0)) ||
		((m_selectGear == Gear::NEUTRAL_GEAR) && (static_cast<Gear>(gear) == Gear::FIRST_GEAR) && (m_speed == 0)) ||
		((static_cast<Gear>(gear) == Gear::NEUTRAL_GEAR)) ||
		((m_selectGear != Gear::REVERSE) && (static_cast<Gear>(gear) >= Gear::FIRST_GEAR) && (m_speed >= 0));
}

bool CCar::IsSpeedInRange(Gear const& gear, int speed) const
{
	auto it = speedRange.find(gear);
	auto speedRange = it->second;
	return  (speedRange.second >= speed) && (speedRange.first <= speed);
}

bool CCar::SetGear(int gear)
{
	bool isSetGear = false;
	bool isAvailableGear = (MAX_GEAR >= gear) && (MIN_GERA <= gear) && m_isOn;
	if (isAvailableGear)
	{
		isSetGear = isAvailableGear && IsSpeedInRange(static_cast<Gear>(gear), std::abs(m_speed)) && CheckGear(gear);
		if (isSetGear)
		{	
			m_selectGear = static_cast<Gear>(gear);
		}
	}
	return isSetGear;
}

bool CCar::SetSpeed(int speed)
{
	bool isSetSpeed = false;
	if (IsSpeedInRange(m_selectGear, speed))
	{
		if (IsNeutralGear() && (speed < std::abs(m_speed)) || !IsNeutralGear())
		{
			m_speed = (Gear::REVERSE == m_selectGear) || (m_speed < 0) ? -speed : speed;
			isSetSpeed = true;
		}
	}
    return isSetSpeed;
}
