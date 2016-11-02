#include "stdafx.h"
#include "Calculator.h"

CRepository CCalculator::GetRepository() const
{
    return m_repository;
}

bool CCalculator::IsDigit(char ch) const
{
    return (ch >= '0') && (ch <= '9');
}

std::string CCalculator::GetFormatValue(std::string const& identifier) const
{
    double value = GetValue(identifier);
    return isnan(value) ? "nan" : str(boost::format("%.2f") % value);
}

double CCalculator::GetValue(std::string const& identifier) const
{
    return m_repository.IsVar(identifier) ? m_repository.GetValueVar(identifier) : GetFnResult(identifier);
}

bool CCalculator::CheckIdentifier(std::string const& identifier) const
{
    bool isIdentifier = true;
    if (!identifier.empty() && !IsDigit(identifier[0]))
    {
        for (char symbol : identifier)
        {
            bool isCorrectSymbol = (symbol >= 'A') && (symbol <= 'Z') || (symbol >= 'a') && 
                (symbol <= 'z') || (symbol == '_') || IsDigit(symbol);
            if (!isCorrectSymbol)
            {
                isIdentifier = false;
            }
        }
    }
    else
    {
        isIdentifier = false;
    }
    return isIdentifier;
}

RuntimeError CCalculator::DefineVar(std::string const& identifier)
{
    RuntimeError wasError = RuntimeError::NO_ERRORS;
    bool isIdentifier = CheckIdentifier(identifier);
    bool isIdentifierDeclared = m_repository.IsIdentifierDeclared(identifier);
    if (!identifier.empty() && isIdentifier && !isIdentifierDeclared)
    {
        m_repository.AddIdentifier(identifier);
    }
    else if (!isIdentifier)
    {
        wasError = RuntimeError::INCORRECTLY_IDENTIFIER;
    }
    else if (isIdentifierDeclared)
    {
        wasError = RuntimeError::THIS_IDENTIFIER_ALREADY_DECLARED;
    }
    return wasError;
}

RuntimeError CCalculator::AssignValue(std::string const& identifier, double value)
{
    RuntimeError wasError = RuntimeError::NO_ERRORS;
    bool isIdentifierDeclared = m_repository.IsIdentifierDeclared(identifier);
    if (CheckIdentifier(identifier))
    {
        if (!isIdentifierDeclared)
        {
            m_repository.AddIdentifier(identifier);
        }
        m_repository.SetValue(identifier, value);
    }
    else
    {
        wasError = RuntimeError::INCORRECTLY_IDENTIFIER;
    }
    return wasError;
}

RuntimeError CCalculator::AssignIdentifier(std::string const& firstIdentifier, std::string const& secondIdentifier)
{
    RuntimeError wasError = RuntimeError::NO_ERRORS;
    if (CheckIdentifier(firstIdentifier) && CheckIdentifier(secondIdentifier))
    {
        if (m_repository.IsIdentifierDeclared(secondIdentifier))
        {
            if (!m_repository.IsVar(firstIdentifier))
            {
                wasError = DefineVar(firstIdentifier);
            }
            double value = GetValue(secondIdentifier);
            m_repository.SetValue(firstIdentifier, value);
        }
        else
        {
            wasError = RuntimeError::SECOND_IDENTIFIER_IS_NOT_DIFINE;
        }
    }
    else
    {
        wasError = RuntimeError::INCORRECTLY_IDENTIFIER;
    }
    return wasError;
}

double CCalculator::CalculationValue(double firstOperandValue, double secondOperandValue, Operation const& operation) const
{
    double result;
    switch (operation)
    {
    case Operation::ADD:
        result = firstOperandValue + secondOperandValue;
        break;
    case Operation::DIV:
        result = firstOperandValue / secondOperandValue;
        break;
    case Operation::MUL:
        result = firstOperandValue * secondOperandValue;
        break;
    case Operation::SUB:
        result = firstOperandValue - secondOperandValue;
        break;
    default:
        break;
    }
    return result;
}

double CCalculator::GetFnResult(std::string const& fnIdentifier) const
{
    double result;
    auto functionRelease = m_repository.GetFunctionRelease(fnIdentifier);
    if (functionRelease.isTwoIdentifier)
    {
        double firstOperandValue = GetValue(functionRelease.firstOperand);
        double secondOperandValue = GetValue(functionRelease.secondOperand);
        result = CalculationValue(firstOperandValue, secondOperandValue, functionRelease.operation);
    }
    else 
    {
        result = GetValue(functionRelease.firstOperand);
    }
    return result;
}

RuntimeError CCalculator::DefineFunction(std::string const& functionIdentifier, FunctionRelease const& functionRelease)
{
    RuntimeError wasError = RuntimeError::NO_ERRORS;
    if (CheckIdentifier(functionIdentifier) && !m_repository.IsIdentifierDeclared(functionIdentifier))
    {
        bool isIdentifierDeclared = m_repository.IsIdentifierDeclared(functionRelease.firstOperand) &&
            m_repository.IsIdentifierDeclared(functionRelease.secondOperand);
        if (functionRelease.isTwoIdentifier && isIdentifierDeclared)
        {
            m_repository.AddFunction(functionIdentifier, functionRelease);
        }
        else if (!functionRelease.isTwoIdentifier && m_repository.IsIdentifierDeclared(functionRelease.firstOperand))
        {
            m_repository.AddFunction(functionIdentifier, functionRelease);
        }
    }
    else if (m_repository.IsIdentifierDeclared(functionIdentifier))
    {
        wasError = RuntimeError::THIS_IDENTIFIER_ALREADY_DECLARED;
    }
    else
    {
        wasError = RuntimeError::INCORRECTLY_IDENTIFIER;
    }
    return wasError;
}