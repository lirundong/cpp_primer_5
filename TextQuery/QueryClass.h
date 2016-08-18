#pragma once
#ifndef _QUERY_CLASS_
#define _QUERY_CLASS_

/*! \brief STL headers */
#include <string>
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

typedef std::vector<std::string>::size_type str_idx;

/*! \brief Class for QueryResult */
class QueryResult {
private:
	std::string _query_key;
	std::set<str_idx> _result_line_idx;
	std::shared_ptr<std::vector<std::string>> _current_text;
public:
	QueryResult():
		_query_key(" "), _result_line_idx({}), _current_text(nullptr) {}
	QueryResult(const std::string &query_key, 
		const std::set<str_idx> &result_line_idx,
		const std::shared_ptr<std::vector<std::string>> current_text):
		_query_key(query_key), _result_line_idx(result_line_idx), _current_text(current_text) { }
	void show_result(std::ostream &os = std::cout);
};
// Functions
void QueryResult::show_result(std::ostream &os) {
	os << _query_key << " occurs " << _result_line_idx.size() << " times:" << std::endl;
	for (auto current_line = _result_line_idx.cbegin(); current_line != _result_line_idx.cend(); ++current_line) {
		os << "#" << *current_line << ": " << (*_current_text)[*current_line] << std::endl;
	}
}

/*! \brief Class for TextQuery */
class TextQuery {
public:
	TextQuery(std::ifstream &ifs);
	// Functions:
	QueryResult query(const std::string &str_in) const;
private:
	std::shared_ptr<std::vector<std::string>> _full_text;
	std::map<std::string, std::set<str_idx>> _word_to_line_idx;
};
// Constructors:
TextQuery::TextQuery(std::ifstream &ifs):
	_full_text(new std::vector<std::string>) {
	std::string str_buffer, word_buffer;
	str_idx current_idx = 0;
	while (std::getline(ifs, str_buffer)) {
		if (str_buffer.length() == 0) {
			++current_idx;
			continue;
		} else {
			_full_text->push_back(str_buffer);
			// build map from word to line idx
			std::istringstream iss(str_buffer);
			while (iss >> word_buffer) {
				_word_to_line_idx[word_buffer].insert(current_idx);
			}
			++current_idx;
		}
	}
}
// Functions:
QueryResult TextQuery::query(const std::string &str_in) const {
	static std::set<str_idx> null_set;
	auto set_idx = _word_to_line_idx.find(str_in);
	if (set_idx != _word_to_line_idx.cend()) {
		return QueryResult(str_in, set_idx->second, _full_text);
	} else {
		return QueryResult(str_in, null_set, _full_text);
	}
}

#endif // !_QUERY_CLASS_
