#pragma once
#include "stdafx.h"
#include "Repository.h"
#include "Var.h"

class CCalculator
{
public:
    CRepository GetRepository() const;
    
    bool CheckIdentifier(std::string const& identifier) const;
    bool IsDigit(char ch) const;

    double CalculationValue(double firstOperandValue, double secondOperandValue, Operation const& operation) const;
    double GetFnResult(std::string const& fnIdentifier) const;
    double GetValue(std::string const& identifier) const;

    std::string GetFormatValue(std::string const& identifier) const;

    RuntimeError DefineVar(std::string const& identifier);
    RuntimeError DefineFunction(std::string const& identifier, FunctionRelease const& functionRelease);
    RuntimeError AssignValue(std::string const& identifier, double value);
    RuntimeError AssignIdentifier(std::string const& firstIdentifier, std::string const& secondIdentifier);
private:
    CRepository m_repository;
};