#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>

#include <Windows.h> 


int main(int argc, char** argv)
{

	SetConsoleCP(CP_UTF8); 
	SetConsoleOutputCP(CP_UTF8); 

	long double value;
	std::string input;
	std::getline(std::cin, input);
	std::istringstream in(input);
	//std::istringstream in("1234 EUR");
	in.imbue(std::locale("de_BE.UTF-8"));
	in >> std::get_money(value);

	value *= 88.93;
	
	std::cout.imbue(std::locale("ru_RU.UTF-8"));
	std::cout << std::showbase << std::put_money(value, false) << '\n';


	system("pause");

	return EXIT_SUCCESS;
}
