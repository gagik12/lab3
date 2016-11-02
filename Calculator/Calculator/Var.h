#pragma once
#include "stdafx.h"

enum class RuntimeError
{
    NO_ERRORS,
    INCORRECTLY_IDENTIFIER,
    THIS_IDENTIFIER_ALREADY_DECLARED,
    INCORRECT_DATA,
    SECOND_IDENTIFIER_IS_NOT_DIFINE,
    IDENTIFIER_IS_NOT_DIFINE,
};

enum class Operation
{
    ADD,
    SUB,
    DIV,
    MUL
};

struct FunctionRelease
{
    std::string firstOperand;
    std::string secondOperand;
    Operation operation;
    bool isTwoIdentifier;
};

typedef std::map<std::string, double> Vars;
typedef std::map<std::string, FunctionRelease> Function;