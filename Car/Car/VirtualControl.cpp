#include "stdafx.h"
#include "VirtualControl.h"
#include "Car.h"

using namespace std;
using namespace std::placeholders;


CVirtualControl::CVirtualControl(CCar & vaz, std::istream & input, std::ostream & output)
	: m_vaz(vaz)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "EngineOn", bind(&CVirtualControl::TurnOnEngine, this, _1) },
		{ "EngineOff", bind(&CVirtualControl::TurnOffEngine, this, _1) },
		{ "SetGear", bind(&CVirtualControl::SetGear, this, _1) },
		{ "SetSpeed", bind(&CVirtualControl::SetSpeed, this, _1) },
		{ "Info", bind(&CVirtualControl::Info, this, _1) },
})
{
}


bool CVirtualControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
	}
	else
	{
		return false;
	}

	return true;
}

bool CVirtualControl::TurnOnEngine(std::istream & /*args*/)
{
	bool isTurnOnEngine = m_vaz.TurnOnEngine();
	std::string output = isTurnOnEngine ? "Engine is turned on\n" : "Engine is already on!\n";
	m_output << output;
	return isTurnOnEngine;
}

bool CVirtualControl::TurnOffEngine(std::istream & /*args*/)
{
	bool isTurnOff = m_vaz.TurnOffEngine();
	std::string output = isTurnOff ? "Engine is turned off\n" : "Engine is already off, not on neutral gear or not zero speed!\n";
	m_output << output;
	return isTurnOff;
}

bool CVirtualControl::SetGear(std::istream & args)
{
	int gear;
	args >> gear;
	bool isSetGear = m_vaz.SetGear(gear);
	std::string output = isSetGear ? "Gear: " + std::to_string(m_vaz.GetGear()) : "Error: Gear can not switch at the moment!";
	m_output << output << endl;
	return isSetGear;
}

bool CVirtualControl::SetSpeed(std::istream & args)
{
	int speed;
	args >> speed;
	bool isSetSpeed = m_vaz.SetSpeed(speed);
    std::string output = isSetSpeed ? "Speed: " + std::to_string(m_vaz.GetCurrentSpeed()) : "Error: Speed is not the same as a valid gear value or gear is neutral!";
	m_output << output << endl;
	return isSetSpeed;
}

bool CVirtualControl::Info(std::istream & /*args*/)
{
	std::string output = m_vaz.IsTurnOnEngine() ? 
		"Engine is turned on\n"  
		"Direction: " + GetDirectionString(m_vaz.GetDirection()) + "\n"
		"Gear: " + std::to_string(m_vaz.GetGear()) + "\n" 
		"Speed: " + std::to_string(m_vaz.GetCurrentSpeed())  + "\n"
		: "Engine is turned off\n";
	m_output << output;
	return true; 
}

std::string CVirtualControl::GetDirectionString(Direction const& direction)
{
	std::string result;
	if (direction == Direction::FORWARD)
	{
		result = "Forward";
	}
	else if (direction == Direction::BACKWARD)
	{
		result = "Backward";
	}
	else
	{
		result = "Standing";
	}
	return result;
}

