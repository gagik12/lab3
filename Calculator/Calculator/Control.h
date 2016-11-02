#pragma once
#include <boost/noncopyable.hpp>
#include "Calculator.h"

class CControl : boost::noncopyable
{
public:
    CControl(CCalculator & calculator, std::istream & input, std::ostream & output);
    bool HandleCommand();
    bool PrintError(RuntimeError const& code);
    bool IsNumber(std::string const& assign);
private:
    bool DefineVar(std::istream & args);
    bool DefineFunction(std::istream & args);
    bool AssignVar(std::istream & args);
    bool PrintVars(std::istream & /*args*/);
    bool PrintFns(std::istream & args);
    bool PrintVar(std::istream & args);
private:
    typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

    CCalculator & m_calculator;
    std::istream & m_input;
    std::ostream & m_output;

    const ActionMap m_actionMap;
};