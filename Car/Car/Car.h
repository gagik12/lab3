#pragma once
#include "stdafx.h"
#include "Const.h"

typedef std::pair<int, int> Speed;
typedef std::map<Gear, Speed> SpeedRange;
extern const SpeedRange speedRange;

class CCar
{
public:
	int GetGear() const;
	int GetCurrentSpeed() const;
	Direction GetDirection() const;
	bool IsTurnOnEngine() const;
	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(int gear);
	bool SetSpeed(int speed);

    bool IsNeutralGear() const;
    bool IsSpeedInRange(Gear const& gear, int speed) const;
    bool CheckGear(int gear) const;
private:
	bool m_isOn = false;
	Gear m_selectGear = Gear::NEUTRAL_GEAR;
	int m_speed = 0;
};
