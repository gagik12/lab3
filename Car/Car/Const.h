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

enum struct Direction
{
	BACKWARD = -1,
	STAND = 0,
	FORWARD = 1,
};
