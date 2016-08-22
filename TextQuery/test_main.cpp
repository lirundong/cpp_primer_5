#include "QueryClass.h"

int main(int argc, char *argv[]) {
	if (argc < 2)
		return -1;

	const std::string TEST_FILE = "test_text.txt";
	std::ifstream inFile(TEST_FILE);

	TextQuery query1(inFile);
	auto result1 = query1.query(argv[1]);
	result1.show_result();

	return 0;
}
