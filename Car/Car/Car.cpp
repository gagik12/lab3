#include "stdafx.h"
#include "Car.h"
#include "Const.h"
#include <iostream>

CCar::CCar()
	:m_speedRange({
		{ Gear::REVERSE, Speed(0, 20) },
		{ Gear::NEUTRAL_GEAR, Speed(MIN_SPEED, MAX_SPEED) },
		{ Gear::FIRST_GEAR, Speed(0, 30) },
		{ Gear::SECOND_GEAR, Speed(20, 50) },
		{ Gear::THIRD_GEAR, Speed(30, 60) },
		{ Gear::FOURTH_GEAR, Speed(40, 90) },
		{ Gear::FIFTH_GEAR, Speed(50, 150) },
})
{
}

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

std::string CCar::GetDirection() const
{
	std::string diraction;
	switch (m_direction)
	{
	case Direction::STAND:
		diraction = "Cтоим на месте";
		break;
	case Direction::FORWARD:
		diraction = "Вперед";
		break;
	case Direction::BACKWARD:
		diraction = "Назад";
		break;
	default:
		break;
	}
	return diraction;
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
		(static_cast<Gear>(gear) >= Gear::FIRST_GEAR);
}

/*
if ((static_cast<Gear>(gear) == Gear::REVERSE) && (m_speed == 0))
{
m_selectGear = static_cast<Gear>(gear);
}
else if ((m_selectGear == Gear::REVERSE) && (static_cast<Gear>(gear) == Gear::FIRST_GEAR) && (m_speed == 0))
{
m_selectGear = static_cast<Gear>(gear);
}
else if ((m_selectGear == Gear::NEUTRAL_GEAR) && (static_cast<Gear>(gear) == Gear::FIRST_GEAR) && (m_speed == 0))
{
m_selectGear = static_cast<Gear>(gear);
}
else if ((static_cast<Gear>(gear) == Gear::NEUTRAL_GEAR))
{
m_selectGear = static_cast<Gear>(gear);
}*/

bool CCar::SetGear(int gear)
{
	bool isSetGear = false;
	bool isAvailableGear = (MAX_GEAR >= gear) && (MIN_GERA <= gear) && m_isOn;
	if (isAvailableGear)
	{
		auto it = m_speedRange.find(static_cast<Gear>(gear));
		auto speedRange = it->second;
		bool isAvailableSpeed = (speedRange.second >= m_speed) && (speedRange.first <= m_speed);

		isSetGear = isAvailableGear && isAvailableSpeed && CheckGear(gear);
		if (isSetGear)
		{	
			m_selectGear = static_cast<Gear>(gear);
		}
	}
	return isSetGear;
}

void CCar::UpdateDirection()
{
	if (m_selectGear == Gear::NEUTRAL_GEAR)
	{
		m_direction = Direction::STAND;
	}
	else if ((m_selectGear == Gear::REVERSE) && (m_speed > 0))
	{
		m_direction = Direction::BACKWARD;
	}
	else if (m_speed > 0)
	{
		m_direction = Direction::FORWARD;
	}
}

bool CCar::SetSpeed(int speed)
{
	bool isSetSpeed = false;
	auto it = m_speedRange.find(static_cast<Gear>(m_selectGear));
	auto speedRange = it->second;
	bool isAvailableSpeed = (speedRange.second >= speed) && (speedRange.first <= speed);
	if (isAvailableSpeed)
	{
		if (IsNeutralGear() && (speed < m_speed) || !IsNeutralGear())
		{
			m_speed = speed;
			UpdateDirection();
			isSetSpeed = true;
		}
	}
    return isSetSpeed;
}
