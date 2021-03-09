#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
int main(int argc, char** argv)
{
	std::string data = R"(vishalchovatiya@ymail.com vishalchovatiya@mail.comhgdvjhgsyfgbxzhg
	,,....  hjgd@@mail.ruhf___&&&63j@rambler.ru)";

	std::regex pattern_1(R"(\w+@(?:mail|rambler)+\.(?:com|ru))");
	

	std::copy(
		std::sregex_token_iterator(data.begin(), data.end(), pattern_1),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));

	std::cout << std::endl;


	system("pause");

	return EXIT_SUCCESS;
}