#pragma once
#ifndef _PRINT_STRING_H_
#define _PRINT_STRING_H_

#include <iostream>
#include <string>

class PrintString {
public:
	PrintString();
	~PrintString();
	std::string &operator()(std::istream &is = std::cin) {
		is >> _null;
		return _null;
	}
private:
	std::string _null;
};

PrintString::PrintString(): _null(" ") {}

PrintString::~PrintString() {}

#endif // !_PRINT_STRING_H_
