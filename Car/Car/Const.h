#pragma once
#include "stdafx.h"

static const int MAX_GEAR = 5;
static const int MIN_GERA = -1;

static const int MIN_SPEED = 0;
static const int MAX_SPEED = 150;

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

typedef std::pair<int, int> Speed;
typedef std::map<Gear, Speed> SpeedRange;
static const SpeedRange speedRange = {
	{ Gear::REVERSE, Speed(0, 20) },
	{ Gear::NEUTRAL_GEAR, Speed(MIN_SPEED, MAX_SPEED) },
	{ Gear::FIRST_GEAR, Speed(0, 30) },
	{ Gear::SECOND_GEAR, Speed(20, 50) },
	{ Gear::THIRD_GEAR, Speed(30, 60) },
	{ Gear::FOURTH_GEAR, Speed(40, 90) },
	{ Gear::FIFTH_GEAR, Speed(50, 150) },
};