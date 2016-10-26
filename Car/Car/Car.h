#pragma once
#include "stdafx.h"
#include "Const.h"


class CCar
{
public:
	int GetGear() const;
	int GetSpeed() const;
	bool IsTurnOnEngine() const;

	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(int gear);
	bool SetSpeed(int speed);
private:
	bool IsNeutralGear() const;
	bool IsSpeedInRange(Gear const& gear, int speed) const;
	bool CheckGear(int gear) const;
	bool m_isOn = false;
	Gear m_selectGear = Gear::NEUTRAL_GEAR;
	int m_speed = 0;
};
