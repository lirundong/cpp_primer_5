#include <string>
#include <fstream>
#include <sstream>
#include <map>

/*! \brief A class for word transfer */
class WordTrans {
public:
	WordTrans();
	~WordTrans();
	/* functions */
	void load_dict(std::ifstream &ifs);
	int do_trans(std::ifstream &ifs, std::ofstream &ofs);

private:
	std::map<std::string, std::string> _dict;
	/* functions */
	std::string &trans(std::string &str_in) {
		auto map_it = _dict.find(str_in);
		if (map_it != _dict.cend())
			return map_it->second;
		else
			return str_in;
	}
};

WordTrans::WordTrans() {}
WordTrans::~WordTrans() {}

/* Functions */
void WordTrans::load_dict(std::ifstream &ifs) {
	std::string key_str, value_str;
	while ((ifs >> key_str) && std::getline(ifs, value_str)) {
		if (value_str.size() > 1)
			_dict[key_str] = value_str.substr(1);
		else
			continue;
	}
}

int WordTrans::do_trans(std::ifstream &ifs, std::ofstream &ofs) {
	int trans_counter = 0;
	std::string current_line, current_word, trans_word;
	while (std::getline(ifs, current_line)) {
		std::stringstream ss_current_line(current_line);
		while (ss_current_line >> current_word) {
			trans_word = trans(current_word);
			ofs << trans_word << " ";
			if (trans_word != current_word)
				++trans_counter;
		}
		ofs << std::endl;
	}
	return trans_counter;
}

/*! \brief Main function */
int main(int argc, char *argv[]) {
	// file path
	const std::string DICT_PATH = "dict.txt";
	const std::string IN_FILE_PATH = "origin.txt";
	const std::string OUT_FILE_PATH = "result.txt";

	WordTrans testTrans;
	std::ifstream idfs(DICT_PATH), iffs(IN_FILE_PATH);
	std::ofstream offs(OUT_FILE_PATH, std::ofstream::app);

	testTrans.load_dict(idfs);
	int trans_counter = testTrans.do_trans(iffs, offs);
	offs << std::endl << "×ª»»ÁË " << trans_counter << " ¸ö´Ê»ã¡£" << std::endl;

	return 0;
}