#include <iostream>
#include <fstream>
#include <chrono>
#include "Windows.h"

import Manuscript;
import Library;
import Temple;
import TempleList;



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	std::ifstream file("test.txt");
	TempleList templeList;
	std::ofstream out_file("output.txt");
	file >> templeList;
	std::cout << templeList;
	templeList.about(std::cout);
}