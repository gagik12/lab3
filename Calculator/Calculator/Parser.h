#pragma once
#include "stdafx.h"
#include "Var.h"

boost::optional<std::vector<std::string>> GetToken(std::string const& data, std::string const& delimiter);
Operation GetOperation(std::string const& operation);
void ParseFunctionRelease(FunctionRelease & functionRelease, std::string const& strParse);