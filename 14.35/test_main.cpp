#include "PrintString.h"
#include <vector>

int main() {
	PrintString ps1;
	std::vector<std::string> vs1;
	std::string buffer;

	for (int i = 0; i < 5; ++i) {
		buffer = ps1();
		vs1.push_back(buffer);
	}

	for(auto elem : vs1) {
		std::cout << elem << '\t';
	}

	return 0;
}