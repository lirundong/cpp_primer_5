#include <fstream>
#include <string>
#include <map>

const std::string FILE_PATH = "test.txt";

class WordCounter {
public:
	WordCounter();
	~WordCounter();
	// Count Words
	//? This can be complied by g++...
	void count(std::istream &is) {
		std::string buffer;
		while (is >> buffer) {
			++_world_count[buffer];
		}
	}
	// Print Result
	void print_result(std::ostream &os) {
		for (const auto &word : _world_count) {
			os << word.first << ": " << word.second << " times." << std::endl;
		}
	 }

private:
	std::map<std::string, size_t> _world_count;
};

WordCounter::WordCounter() {}

WordCounter::~WordCounter() {}

int main(int argc, char *argv[]) {
	WordCounter counter1;
	std::ifstream inFile(FILE_PATH);
	std::ofstream outFile(FILE_PATH, std::ofstream::app);

	counter1.count(inFile);
	counter1.print_result(outFile);

	return 0;
}