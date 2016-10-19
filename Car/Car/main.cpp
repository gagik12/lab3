// Car.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Car.h"
#include "VirtualControl.h"

int main()
{
	setlocale(LC_ALL, "rus");
	CCar vaz;
	CVirtualControl virtualControl(vaz, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!virtualControl.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}
	return 0;
}

