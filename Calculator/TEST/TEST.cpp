// TrimBlanksTests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../Calculator/Calculator.h"
#include <boost/function.hpp>

struct CCalculatorFixture
{
    CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(Calculator, CCalculatorFixture)
    BOOST_AUTO_TEST_CASE(can_determine_the_identifier)
    {
        BOOST_CHECK(calculator.DefineVar("x") == RuntimeError::NO_ERRORS);
    }

    BOOST_AUTO_TEST_CASE(identifier_can_not_start_with_a_digit)
    {
        BOOST_CHECK(calculator.DefineVar("2size") == RuntimeError::INCORRECTLY_IDENTIFIER);
    }

    BOOST_AUTO_TEST_CASE(identifier_can_not_be_empty)
    {
        BOOST_CHECK(calculator.DefineVar("") == RuntimeError::INCORRECTLY_IDENTIFIER);
    }

    BOOST_AUTO_TEST_CASE(identifier_can_not_be_re_declared)
    {
        BOOST_CHECK(calculator.DefineVar("position") == RuntimeError::NO_ERRORS);
        BOOST_CHECK(calculator.DefineVar("position") == RuntimeError::THIS_IDENTIFIER_ALREADY_DECLARED);
    }

    BOOST_AUTO_TEST_CASE(identifier_can_only_be_letters_of_the_english_alphabet)
    {
        BOOST_CHECK(calculator.DefineVar("позиция") == RuntimeError::INCORRECTLY_IDENTIFIER);
        BOOST_CHECK(calculator.DefineVar("position") == RuntimeError::NO_ERRORS);
    }

    BOOST_AUTO_TEST_CASE(in_the_identifier_can_be_an_underscore)
    {
        BOOST_CHECK(calculator.DefineVar("rectangle_position") == RuntimeError::NO_ERRORS);
    }

    BOOST_AUTO_TEST_CASE(in_the_identifier_may_not_be_other_special_characters)
    {
        BOOST_CHECK(calculator.DefineVar("rectangle+position") == RuntimeError::INCORRECTLY_IDENTIFIER);
    }

    BOOST_AUTO_TEST_CASE(after_the_declaration_of_its_identifier_value_equal_to_nan)
    {
        std::string identifier = "position";
        BOOST_CHECK(calculator.DefineVar(identifier) == RuntimeError::NO_ERRORS);
        BOOST_CHECK(isnan(calculator.GetRepository().GetValueVar(identifier)));
    }

    BOOST_AUTO_TEST_CASE(can_assign_a_variable_value)
    {
        std::string identifier = "position";
        double value = 10.3;
        BOOST_CHECK(calculator.DefineVar(identifier) == RuntimeError::NO_ERRORS);
        calculator.AssignValue(identifier, 10.3);
        BOOST_CHECK(calculator.GetRepository().GetValueVar(identifier) == value);
    }

    struct when_variables_are_define_ : CCalculatorFixture
    {
        when_variables_are_define_()
        {
            calculator.DefineVar("bodySize");
            calculator.AssignValue("bodySize", 10.2);
            calculator.DefineVar("spriteSize");
            calculator.AssignValue("spriteSize", 4.2);
        }
    };
    BOOST_FIXTURE_TEST_SUITE(when_variables_are_define, when_variables_are_define_)
        BOOST_AUTO_TEST_CASE(can_assign_an_identifier)
        {
            BOOST_CHECK(calculator.AssignIdentifier("bodySize", "spriteSize") == RuntimeError::NO_ERRORS);
            BOOST_CHECK(calculator.GetRepository().GetValueVar("bodySize") == calculator.GetRepository().GetValueVar("spriteSize"));
        }

        BOOST_AUTO_TEST_CASE(can_define_a_variable_if_the_identifier_wast_declared_previously)
        {
            BOOST_CHECK(calculator.AssignIdentifier("sizeX", "spriteSize") == RuntimeError::NO_ERRORS);
            BOOST_CHECK(calculator.GetRepository().GetValueVar("sizeX") == calculator.GetRepository().GetValueVar("spriteSize"));
        }

        BOOST_AUTO_TEST_CASE(can_override)
        {
            double value = 24.74;
            BOOST_CHECK(calculator.AssignValue("spriteSize", value) == RuntimeError::NO_ERRORS);
            BOOST_CHECK(calculator.GetRepository().GetValueVar("spriteSize") == 24.74);
        }
        struct create_a_variable_for_the_function_definition_ : CCalculatorFixture
        {
            create_a_variable_for_the_function_definition_ ()
            {
                calculator.DefineVar("fisrtOperand");
                calculator.AssignValue("fisrtOperand", 20);
                calculator.DefineVar("secondOperand");
                calculator.AssignValue("secondOperand", 80);
            }
        };
        BOOST_FIXTURE_TEST_SUITE(create_a_variable_for_the_function_definition, create_a_variable_for_the_function_definition_)
            BOOST_AUTO_TEST_CASE(can_declare_and_return_the_result_of_the_function)
            {
                FunctionRelease functionRelease = {"fisrtOperand", "secondOperand", Operation::DIV, true};
                BOOST_CHECK(calculator.DefineFunction("Div", functionRelease) == RuntimeError::NO_ERRORS);
                BOOST_CHECK(calculator.GetFnResult("Div") == 0.25);
            }

            BOOST_AUTO_TEST_CASE(can_declare_a_function_that_returns_the_value_of_the_variable)
            {
                BOOST_CHECK(calculator.DefineVar("bodySize") == RuntimeError::NO_ERRORS);
                BOOST_CHECK(calculator.AssignValue("bodySize", 10.2) == RuntimeError::NO_ERRORS);
                FunctionRelease functionRelease;
                functionRelease.firstOperand = "bodySize";
                functionRelease.isTwoIdentifier = false;
                BOOST_CHECK(calculator.DefineFunction("ValueVariable", functionRelease) == RuntimeError::NO_ERRORS);
                BOOST_CHECK(calculator.GetFnResult("ValueVariable") == 10.2);
            }

            struct declare_variables_for_the_Fibonacci_formula_ : CCalculatorFixture
            {
                declare_variables_for_the_Fibonacci_formula_()
                {
                    calculator.DefineVar("v0");
                    calculator.AssignValue("v0", 0);
                    calculator.DefineVar("v1");
                    calculator.AssignValue("v1", 1);
                    BOOST_CHECK(calculator.DefineFunction("f0", { "v0", "",  Operation::ADD, false }) == RuntimeError::NO_ERRORS);
                    BOOST_CHECK(calculator.DefineFunction("f1", { "v1", "",  Operation::ADD, false }) == RuntimeError::NO_ERRORS);
                }
            };
            BOOST_FIXTURE_TEST_SUITE(declare_variables_for_the_Fibonacci_formula, declare_variables_for_the_Fibonacci_formula_)
                BOOST_AUTO_TEST_CASE(can_calculate_Fibonacci_numbers)
                {
                    for (int i = 2; i != 100; i++)
                    {
                        FunctionRelease functionRelease = { "f" + std::to_string(i - 2), "f" + std::to_string(i - 1),  Operation::ADD, true };
                        BOOST_CHECK(calculator.DefineFunction("f" + std::to_string(i), functionRelease) == RuntimeError::NO_ERRORS);
                    }
                    //BOOST_CHECK(calculator.GetFnResult("f25") == 75025);
                }
            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
