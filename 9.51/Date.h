#pragma once
#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost\algorithm\string.hpp>
// Monthes:
std::vector<std::string> _MONTHES_ = { "January", "February", "March", "April", "May", "June", "July", "August",
	"September", "October", "November", "December", "January" };
std::string _DIGITS_ = "0123456789-=.";

class Date {
private:
	unsigned int _year = 0, _month = 0, _day = 0;

	std::string num_to_month() {
		return _MONTHES_[_month];
	}

	int month_to_num(const std::string &s_month) {
		auto idx = std::find(_MONTHES_.begin(), _MONTHES_.end(), s_month);
		if (idx != _MONTHES_.end()) {
			return idx - _MONTHES_.begin();
		} else {
			return 0;
		}
	}

public:
	Date() = default;

	Date(const std::string &date_in) {
		Date temp_Date;
		temp_Date.reload(date_in);
	}

	void reload(const std::string &date_in) {
		// this will be faster:
		std::vector<std::string> tokens;
		boost::split(tokens, date_in, boost::is_any_of(",- /\\\t"));

		for (auto idx = tokens.begin(); idx != tokens.end(); ++idx) {
			auto num_idx = (*idx).find_first_of(_DIGITS_);
			if (num_idx == std::string::npos) {
				// no digits... must be month
				_month = month_to_num(*idx);
			} else {
				unsigned int num_temp = std::stoul(*idx);
				if (num_temp > 31u) {
					_year = num_temp;
				} else {
					_day = num_temp;
				}
			}
		}
	}

	void display_date() {
		std::cout << _year << '-' << num_to_month() << '-' << _day << std::endl;
	}
};
#endif // !DATE_H_
