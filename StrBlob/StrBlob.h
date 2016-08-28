#pragma once
#ifndef _STR_BLOB_H_
#define _STR_BLOB_H_

#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <initializer_list>

class StrBlobPtr;

/*! \brief Class: StrBlob */
class StrBlob {
	friend class StrBlobPtr;
public:
	using size_type = std::vector<std::string>::size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	~StrBlob();

	// Function: read only
	bool empty() const { return _data->empty(); }
	size_type size() const { return _data->size(); }
	// front() for non-const
	std::string &front() {
		check(0, "front() on empty StrBlob");
		return _data->front();
	}
	// front() for const
	const std::string &front() const {
		check(0, "front() on empty StrBlob");
		return *_data->cbegin();
	}
	// back() for non-const
	std::string &back() {
		check(0, "back() on empty StrBlob");
		return _data->back();
	}
	// back() for const
	const std::string &back() const {
		check(0, "back() on empty StrBlob");
		return *_data->cend();
	}
	// begin() and end()
	StrBlobPtr begin();
	StrBlobPtr end();
	// operator[]
	std::string &operator[](std::size_t n) {
		return (*_data)[n];
	}
	const std::string &operator[](std::size_t n) const {
		return (*_data)[n];
	}

	// Function: write or delete elements
	void push_bask(const std::string &str_in) { _data->push_back(str_in); }
	void pop_back() {
		check(0, "pop_back() on empty StrBlob");
		_data->pop_back();
	}

private:
	std::shared_ptr<std::vector<std::string>> _data;
	// check idx of _data[idx]
	void check(size_type idx, const std::string &msg) const {
		if (idx >= _data->size() || idx < 0)
			throw std::out_of_range(msg);
	}
};

/*! \brief Class: StrBlobPtr, pointer for StrBlob */
class StrBlobPtr {
public:
	StrBlobPtr() :_idx(0) {};
	StrBlobPtr(StrBlob &a, std::size_t idx = 0) :
		_wptr(a._data), _idx(idx) {}
	~StrBlobPtr();

	// Function: read only
	std::string &dref() const;  // de-referance *this
	// operator * and ->
	std::string &operator*() const {
		auto p = check(_idx, "de - referance past end");
		return (*p)[_idx];
	}
	std::string *operator->() const {
		auto p = check(_idx, "de - referance past end");
		return & this->operator*;
	}

	// Function: change instance
	StrBlobPtr &incr();  // add _idx
	// pre-operator ++ and --
	StrBlobPtr &operator++() {
		check(_idx, "increasement past end of StrBlobPtr");
		++_idx;
		return *this;
	}
	StrBlobPtr &operator--() {
		--_idx;
		check(_idx, "decreasement at begin of StrBlobPtr");
		return *this;
	}
	// post-operator ++ and --, call pre-operator
	StrBlobPtr operator++(int) {
		StrBlobPtr back_up = *this;
		++*this;
		return back_up;
	}
	StrBlobPtr operator--(int) {
		StrBlobPtr back_up = *this;
		--*this;
		return back_up;
	}
	// operator + and -
	StrBlobPtr &operator+(int n) {
		_idx += n;
		check(_idx, "increasement past end of StrBlobPtr");
		return *this;
	}
	StrBlobPtr &operator-(int n) {
		_idx -= n;
		check(_idx, "decreasement at begin of StrBlobPtr");
		return *this;
	}

private:
	std::size_t _idx;  // index in _data vector
	std::weak_ptr<std::vector<std::string>> _wptr;
	// check() if vector exists, NOTE: shared_ptr here
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t idx, const std::string &msg) const;
};

/*! \brief Functions in SreBlob */
inline StrBlob::StrBlob() :
	_data(std::make_shared<std::vector<std::string>>()) {}

inline StrBlob::StrBlob(std::initializer_list<std::string> il) :
	_data(std::make_shared<std::vector<std::string>>(il)) {}

inline StrBlob::~StrBlob() {}

inline StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
inline StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, _data->size()); }

/*! \brief Functions in SreBlobPtr */
inline StrBlobPtr::~StrBlobPtr() {}

inline std::string & StrBlobPtr::dref() const {
	auto curr_ptr = check(_idx, "de-referance past end");
	return (*curr_ptr)[_idx];
}

inline StrBlobPtr & StrBlobPtr::incr() {
	check(_idx, "increasement past end of StrBlobPtr");
	++_idx;
	return *this;
}

inline std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t idx, const std::string & msg) const {
	auto ret = _wptr.lock();
	if (!ret)  // vector _data doesn't exist
		throw std::runtime_error("unbound StrBlobPrt");
	else if (idx >= ret->size() || idx < 0)  // invalid idx
		throw std::out_of_range(msg);
	else  // now ret points at _data
		return ret;
}

#endif // !_STR_BLOB_H_
