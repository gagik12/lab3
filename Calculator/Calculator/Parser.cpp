#include "stdafx.h"
#include "Parser.h"
#include "Var.h"

boost::optional<std::vector<std::string>> GetToken(std::string const& data, std::string const& delimiter)
{
    std::vector<std::string> token;
    boost::split(token, data, boost::is_any_of(delimiter));
    if (token.size() != 2)
    {
        return{};
    }
    return token;
}

Operation GetOperation(std::string const& operation)
{
    Operation result;
    if (operation == "+")
    {
        result = Operation::ADD;
    }
    else if (operation == "-")
    {
        result = Operation::SUB;
    }
    else if (operation == "/")
    {
        result = Operation::DIV;
    }
    else
    {
        result = Operation::MUL;
    }
    return result;
}


void ParseFunctionRelease(FunctionRelease & functionRelease, std::string const& data)
{
    const std::set<std::string> signsOperation = { "+", "-", "/", "*" };
    boost::optional<std::vector<std::string>> token;
    for (auto signOperation : signsOperation)
    {
        token = GetToken(data, signOperation);
        if (token.is_initialized()) //При fn result=GetSum+GetSub
        {
            functionRelease.firstOperand = token->at(0);
            functionRelease.operation = GetOperation(signOperation);
            functionRelease.secondOperand = token->at(1);
            functionRelease.isTwoIdentifier = true;
            break;
        }
    }
    if (!token.is_initialized()) //При fn sum=GetSum
    {
        functionRelease.firstOperand = data;
        functionRelease.isTwoIdentifier = false;
    }
}