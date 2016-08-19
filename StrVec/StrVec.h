#pragma once
#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <memory>
#include <utility>
#include <string>

/*********************
 * Classes
 *********************/
class StrVec {
public:
	StrVec();
	StrVec(const StrVec &);
	~StrVec();
	// read-only:
	std::size_t size() const { return _first_free - _elem; }
	std::size_t capacity() const { return _cap - _elem; }
	std::string* begin() { return _elem; }
	std::string* cbegin() const { return _elem; }
	std::string* end() { return _first_free; }
	std::string* cend() const { return _first_free; }
	// add , remove or change elements:
	void push_back(const std::string &s);
	StrVec& operator=(const StrVec &);
private:
	std::string *_elem, *_first_free, *_cap;
	std::allocator<std::string> _alloc;
	// functions:
	void reallocate() {
		auto new_capacity = size() ? 2 * size() : 1;
		auto new_mem = _alloc.allocate(new_capacity);
		auto dest = new_mem;  // copy origin data to here
		auto orig_elem = _elem;  // origin data for copy
		while (orig_elem != _first_free)
			_alloc.construct(dest++, std::move(*orig_elem++));
		free();
		_elem = new_mem;
		_first_free = dest;
		_cap = _elem + new_capacity;
	}
	void free() {
		if (_elem) {
			while (_first_free != _elem)
				_alloc.destroy(--_first_free);
			_alloc.deallocate(_elem, _cap - _elem);
		}
	}
	void check_n_alloc() {
		if (size() == capacity())
			reallocate();
	}
	std::pair<std::string*, std::string*>  // return: _elem, _first_free
		alloc_n_copy(const std::string *b, const std::string *e) {
		auto data = _alloc.allocate(e - b);  // new memory enough for b to e
		return { data, std::uninitialized_copy(b, e, data) };
	}
};

/*********************
 * Functions
 *********************/
StrVec::StrVec():
	_elem(nullptr), _first_free(nullptr), _cap(nullptr) { }

StrVec::StrVec(const StrVec &s){
	auto new_data = alloc_n_copy(s.cbegin(), s.cend());
	_elem = new_data.first;
	_cap = _first_free = new_data.second;
}

StrVec::~StrVec() { free(); }

void StrVec::push_back(const std::string &s) {
	check_n_alloc();
	_alloc.construct(_first_free++, s);
}

StrVec& StrVec::operator=(const StrVec &rs) {
	auto new_data = alloc_n_copy(rs.cbegin(), rs.cend());
	free();
	_elem = new_data.first;
	_cap = _first_free = new_data.second;
	return *this;
}
#endif // !_STR_VEC_H_
