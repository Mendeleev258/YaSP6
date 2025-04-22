#include <iostream>
#include <fstream>
#include <chrono>
#include "Windows.h"

import Manuscript;
import Library;
import Temple;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Temple temple1{};
	std::ifstream file("test.txt");
	file >> temple1;
	std::cout << temple1;

	file.clear();
	Temple temple2{};
	file >> temple2;
	std::cout << temple2;
}