#include "stdafx.h"
#include "Control.h"
#include "Parser.h"

using namespace std;
using namespace std::placeholders;

CControl::CControl(CCalculator & calculator, std::istream & input, std::ostream & output)
    : m_calculator(calculator)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
        { "var", bind(&CControl::DefineVar, this, _1) },
        { "let", bind(&CControl::AssignVar, this, _1) },
        { "printvars", bind(&CControl::PrintVars, this, _1) },
        { "print", bind(&CControl::PrintVar, this, _1) },
        { "fn", bind(&CControl::DefineFunction, this, _1) },
        { "printfns", bind(&CControl::PrintFns, this, _1) },
})
{
}

bool CControl::HandleCommand()
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

bool CControl::DefineVar(std::istream & args)
{
    std::string identifier;
    args >> identifier;
    auto wasError = m_calculator.DefineVar(identifier);
    return PrintError(wasError);
}


bool CControl::IsNumber(std::string const& assign)
{
    bool isNumber = true;
    try
    {
        boost::lexical_cast<double>(assign);
    }
    catch (boost::bad_lexical_cast)
    {
        isNumber = false;
    }
    return isNumber;
}

bool CControl::AssignVar(std::istream & args)
{
    auto wasError = RuntimeError::NO_ERRORS;
    std::string data;
    args >> data;
    boost::optional<std::vector<std::string>> token = GetToken(data, "=");
    if (token.is_initialized() && IsNumber(token->at(1)))
    {
        wasError = m_calculator.AssignValue(token->at(0), boost::lexical_cast<double>(token->at(1)));
    }
    else if(token.is_initialized() && m_calculator.CheckIdentifier(token->at(1)))
    {
        wasError = m_calculator.AssignIdentifier(token->at(0), token->at(1));
    }
    else
    {
        wasError = RuntimeError::INCORRECT_DATA;
    }
    return PrintError(wasError);
}

bool CControl::PrintError(RuntimeError const& code)
{
    bool isWasError = true;
    switch (code)
    {
    case RuntimeError::INCORRECTLY_IDENTIFIER:
        m_output << "INCORRECTLY IDENTIFIER!!!\n";
        break;
    case RuntimeError::THIS_IDENTIFIER_ALREADY_DECLARED:
        m_output << "THIS IDENTIFIER ALREADY DECLARED!!!\n";
        break;
    case RuntimeError::INCORRECT_DATA:
        m_output << "INPUT DATA IS NOT CORRECT!!!\n";
        break;
    case RuntimeError::SECOND_IDENTIFIER_IS_NOT_DIFINE:
        m_output << "SECOND IDENTIFIER IS NOT DIFINE!!!\n";
        break;
    case RuntimeError::IDENTIFIER_IS_NOT_DIFINE:
        m_output << "IDENTIFIER IS NOT DIFINE!!!\n";
        break;
    default:
        isWasError = false;
        break;
    }
    return isWasError;
}

bool CControl::PrintVars(std::istream & /*args*/)
{
    auto vars = m_calculator.GetRepository().GetVars();
    for (auto var : vars)
    {
        m_output << var.first << ":" << m_calculator.GetFormatValue(var.first) << std::endl;
    }
    return true;
}

bool CControl::PrintVar(std::istream & args)
{
    auto wasError = RuntimeError::NO_ERRORS;
    std::string identifier;
    args >> identifier;
    if (m_calculator.CheckIdentifier(identifier))
    {
        if (m_calculator.GetRepository().IsIdentifierDeclared(identifier))
        {
            m_output << identifier << ":" << m_calculator.GetFormatValue(identifier) << std::endl;
        }
        else
        {
            wasError = RuntimeError::IDENTIFIER_IS_NOT_DIFINE;
        }
    }
    else
    {
        wasError = RuntimeError::INCORRECTLY_IDENTIFIER;
    }
    return PrintError(wasError);
}

bool CControl::DefineFunction(std::istream & args)
{
    auto wasError = RuntimeError::NO_ERRORS;
    std::string function;
    args >> function;
    boost::optional<std::vector<std::string>> token = GetToken(function, "=");
    if (token.is_initialized())
    {
        FunctionRelease functionRelease;
        ParseFunctionRelease(functionRelease, token->at(1));
        wasError = m_calculator.DefineFunction(token->at(0), functionRelease);
    }
    else
    {
        wasError = RuntimeError::INCORRECT_DATA;
    }
    return PrintError(wasError);
}

bool CControl::PrintFns(std::istream & args)
{
    auto functions = m_calculator.GetRepository().GetFunctions();
    for (auto function : functions)
    {
        m_output << function.first << ":" << m_calculator.GetFormatValue(function.first) << std::endl;
    }
    return true;
}