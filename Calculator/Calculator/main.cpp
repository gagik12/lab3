#include "stdafx.h"
#include "Calculator.h"
#include "Control.h"

int main()
{
    CCalculator calculator;
    CControl control(calculator, std::cin, std::cout);

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << ">";
        if (!control.HandleCommand())
        {
            std::cout << "Unknown command!\n";
        }
    }
    return 0;
}
