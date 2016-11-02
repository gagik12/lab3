#include "stdafx.h"
#include "../Calculator/Control.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// Зависимости RemoteControl-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструирования самого remote-контрола
struct ControlDependencies
{
    CCalculator calculator;
    stringstream input;
    stringstream output;
};

struct ControlFixture :ControlDependencies
{
    CControl control;
    ControlFixture()
        : control(calculator, input, output)
    {
    }

    void StartCommandHandling(const string& command, const string& expectedOutput)
    {
        input = stringstream();
        BOOST_CHECK(input << command);
        BOOST_CHECK(control.HandleCommand());
        BOOST_CHECK_EQUAL(output.str(), expectedOutput);
    }
};

BOOST_FIXTURE_TEST_SUITE(Control, ControlFixture)

    BOOST_AUTO_TEST_CASE(can_handle_var_command)
    {
        std::string identifier = "x";
        StartCommandHandling("var " + identifier, "");
        BOOST_CHECK(calculator.GetRepository().GetVars().find(identifier)->first == identifier);
        BOOST_CHECK(isnan(calculator.GetRepository().GetValueVar(identifier)));
    }

    BOOST_AUTO_TEST_CASE(can_handle_let_identifier_and_value_command)
    {
        std::string identifier = "x";
        double value = 12.34;
        StartCommandHandling("var " + identifier, "");
        StartCommandHandling("let " + identifier + "=" + std::to_string(value), "");
        BOOST_CHECK(calculator.GetRepository().GetValueVar(identifier) == value);
    }

    BOOST_AUTO_TEST_CASE(can_handle_let_identifier_and_identifier_command)
    {
        std::string firstIdentifier = "x";
        std::string secondIdentifier = "y";
        double value = 12.34;
        StartCommandHandling("var " + firstIdentifier, "");
        StartCommandHandling("let " + firstIdentifier + "=10.42", "");
        StartCommandHandling("var " + secondIdentifier, "");
        StartCommandHandling("let " + secondIdentifier + "=20.62", "");
        StartCommandHandling("let " + firstIdentifier + "=" + secondIdentifier, "");
        BOOST_CHECK(calculator.GetRepository().GetValueVar(firstIdentifier) == 20.62);
    }

    BOOST_AUTO_TEST_CASE(command_var_can_output_error)
    {
        std::string identifier = "2x";
        StartCommandHandling("var " + identifier, "INCORRECTLY IDENTIFIER!!!\n");
    }

    BOOST_AUTO_TEST_CASE(command_let_can_output_error)
    {
        std::string identifier = "x";
        StartCommandHandling("let " + identifier + "=10.42", "");
    }

    BOOST_AUTO_TEST_CASE(can_handle_print_command)
    {
        std::string identifier = "position";
        StartCommandHandling("var " + identifier, "");
        StartCommandHandling("let " + identifier + "=10.42", "");
        std::string expectedOutput = identifier + ":10.42\n";
        StartCommandHandling("print " + identifier, expectedOutput);
    }

    BOOST_AUTO_TEST_CASE(can_handle_printvars_command)
    {
        StartCommandHandling("var radius", "");
        StartCommandHandling("let radius=10.42", "");
        StartCommandHandling("var size", "");
        std::string expectedOutput = "radius:10.42\nsize:nan\n";
        StartCommandHandling("printvars", expectedOutput);
    }

    BOOST_AUTO_TEST_CASE(can_handle_fn_command)
    {
        StartCommandHandling("let radius=10", "");
        StartCommandHandling("let pi=3.14", "");
        StartCommandHandling("fn radiusSquared=radius*radius", "");
        StartCommandHandling("fn area=radiusSquared*pi", "");
        BOOST_CHECK(calculator.GetValue("area") == 314);
    }
BOOST_AUTO_TEST_SUITE_END()