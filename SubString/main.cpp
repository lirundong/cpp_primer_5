# include <algorithm>
# include <iostream>
# include <string>
# include <stdexcept>

int main(int argc, char *argv[]) {
	if (argc < 3)
		throw std::invalid_argument("At least two input string.");

	std::string str1(argv[1]);
	std::string str2(argv[2]);

	auto result = std::search(str1.cbegin(), str1.cend(), str2.cbegin(), str2.cend());
	if (result == str1.cend())
		throw std::invalid_argument("No sub-string match.");
	else
		std::cout << "Sub-string index: " << result - str1.begin()
		<< ".\n";
	return 0;
}
