#pragma once
#include <boost/noncopyable.hpp>

class CCar;

class CVirtualControl : boost::noncopyable
{
public:
	CVirtualControl(CCar & vaz, std::istream & input, std::ostream & output);
	bool HandleCommand();

private:
	bool TurnOnEngine(std::istream & args);
	bool TurnOffEngine(std::istream & args);
	bool SetGear(std::istream & args);
	bool SetSpeed(std::istream & args);
	bool Info(std::istream & args);
private:
	typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

	CCar & m_vaz;
	std::istream & m_input;
	std::ostream & m_output;

	const ActionMap m_actionMap;
};