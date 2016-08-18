#include <iostream>
#include <fstream>
#include "StrBlob.h"

const char *FILE_PATH = "test_text.txt";

int main(int argc, char *argv[]) {
	StrBlob SB1;
	std::ifstream ifs(FILE_PATH);
	std::string line;
	while (std::getline(ifs, line)) {
		if (line.length() == 0)
			continue;
		else
			SB1.push_bask(line);
	}

	StrBlobPtr SBP1(SB1);
	// std::cout << SBP1.dref();
	try {
		while (true) {
			std::cout << SBP1.dref();
			SBP1.incr();
		}
	} catch (std::out_of_range err) {
		return 0;
	}
	return 0;
}
