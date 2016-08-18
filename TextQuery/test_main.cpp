#include "QueryClass.h"

int main(int argc, char *argv[]) {
	const std::string TEST_FILE = "test_text.txt";
	std::ifstream inFile(TEST_FILE);

	TextQuery query1(inFile);
	auto result1 = query1.query("demo");

	result1.show_result();
	return 0;
}
