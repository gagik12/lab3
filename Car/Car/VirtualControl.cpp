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
	std::string output = m_vaz.TurnOnEngine() ? "Engine is turned on\n" : "Engine is already on!\n";
	m_output << output;
	return true;
}

bool CVirtualControl::TurnOffEngine(std::istream & /*args*/)
{
	std::string output = m_vaz.TurnOffEngine() ? "Engine is turned off\n" : "Engine is already off, not on neutral gear or not zero speed!\n";
	m_output << output;
	return true;
}

bool CVirtualControl::SetGear(std::istream & args)
{
	int number;
	args >> number;
	std::string output = m_vaz.SetGear(number) ? "Gear: " + std::to_string(m_vaz.GetGear()) : "Error: Gear can not switch at the moment!";
	m_output << output << endl;
	return true;
}

bool CVirtualControl::SetSpeed(std::istream & args)
{
	int number;
	args >> number;
    std::string output = m_vaz.SetSpeed(number) ? "Speed: " + std::to_string(m_vaz.GetSpeed()) : "Error: Speed is not the same as a valid gear value!";
	m_output << "Speed: " << m_vaz.GetSpeed() << endl;
	return true;
}

bool CVirtualControl::Info(std::istream & /*args*/)
{
	std::string output = m_vaz.IsTurnOnEngine() ? 
		"Engine is turned on\n"  
		"Direction: " + m_vaz.GetDirection() + "\n"
		"Gear: " + std::to_string(m_vaz.GetGear()) + "\n" 
		"Speed: " + std::to_string(m_vaz.GetSpeed())  + "\n"
		: "Engine is turned off\n";
	m_output << output;
	return true; 
}
