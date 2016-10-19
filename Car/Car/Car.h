#pragma once
#include "stdafx.h"

enum class Gear
{
	REVERSE = -1,
	NEUTRAL_GEAR = 0,
	FIRST_GEAR = 1,
	SECOND_GEAR = 2,
	THIRD_GEAR = 3,
	FOURTH_GEAR = 4,
	FIFTH_GEAR = 5,
};

enum class Direction
{
	STAND,
	FORWARD,
	BACKWARD,
};

typedef std::pair<int, int> Speed;
typedef std::map<Gear, Speed> SpeedRange;

class CCar
{
public:
	CCar();
	int GetGear() const;
	int GetSpeed() const;
	bool IsTurnOnEngine() const;
	std::string CCar::GetDirection() const;

	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(int channel);
	bool SetSpeed(int speed);

private:
	bool IsNeutralGear() const;
	void UpdateDirection();
	bool CheckGear(int gear) const;
	bool m_isOn = false;
	Gear m_selectGear = Gear::NEUTRAL_GEAR;
	int m_speed = 0;
	Direction m_direction = Direction::STAND;
	SpeedRange m_speedRange;
};
