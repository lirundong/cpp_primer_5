#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void elimDups(std::vector<std::string> &words) {
	// Sort by dictionary & Unique
	std::sort(words.begin(), words.end());
	auto endUnique = std::unique(words.begin(), words.end());
	words.erase(endUnique, words.end());
	// Sort by word length
	std::stable_sort(words.begin(), words.end(),
		[](const std::string &word1, const std::string &word2) {return word1.size() < word2.size(); });
}

void biggies(std::vector<std::string> &words,
	std::vector<std::string>::size_type sz) {
	elimDups(words);
	// Find first size() >= sz
	auto firstIdx = std::find_if(words.begin(), words.end(),
		[&sz](const std::string &word) {return word.size() >= sz; });
	auto wordsCount = words.end() - firstIdx;
	std::cout << "There're " << wordsCount << " words longger than "
		<< sz << ":\n";
	std::for_each(firstIdx, words.end(),
		[](const std::string &word) {std::cout << word << " "; });
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	std::vector<std::string> wordsList{ "Bravo", "Charle", "Apple", "Delta", "Eco", "Delta" };
	biggies(wordsList, 6);

	return 0;
}