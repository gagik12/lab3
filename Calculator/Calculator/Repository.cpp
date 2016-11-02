#include "stdafx.h"
#include "Repository.h"

Vars CRepository::GetVars() const
{
    return m_vars;
}

Function CRepository::GetFunctions() const
{
    return m_function;
}

FunctionRelease CRepository::GetFunctionRelease(std::string const& identifier) const
{
    return m_function.find(identifier)->second;
}

bool CRepository::IsFunction(std::string const& identifier) const
{
    return m_function.find(identifier) != m_function.end();
}

bool CRepository::IsVar(std::string const& identifier) const
{
    return m_vars.find(identifier) != m_vars.end();
}

double CRepository::GetValueVar(std::string const& identifier) const
{
    return m_vars.find(identifier)->second;
}

bool CRepository::IsIdentifierDeclared(std::string const& identifier) const
{
    return IsFunction(identifier) || IsVar(identifier);
}

void CRepository::AddIdentifier(std::string const& identifier)
{
    m_vars.emplace(identifier, NAN);
}

void CRepository::SetValue(std::string const& identifier, double value)
{
    auto var = m_vars.find(identifier);
    var->second = value;
}

void CRepository::AddFunction(std::string const& functionIdentifier, FunctionRelease const& functionRelease)
{
    m_function.emplace(functionIdentifier, functionRelease);
}