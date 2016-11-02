#pragma once
#include "stdafx.h"
#include "Var.h"

class CRepository
{
public:
    Function GetFunctions() const;
    Vars GetVars() const;
    double GetValueVar(std::string const& identifier) const;
    FunctionRelease CRepository::GetFunctionRelease(std::string const& identifier) const;

    bool IsIdentifierDeclared(std::string const& identifier) const;
    bool IsFunction(std::string const& identifier) const;
    bool IsVar(std::string const& identifier) const;

    void AddIdentifier(std::string const& identifier);
    void AddFunction(std::string const& identifier, FunctionRelease const& functionRelease);
    void SetValue(std::string const& identifier, double value);
private:
    Vars m_vars;
    Function m_function;
};
