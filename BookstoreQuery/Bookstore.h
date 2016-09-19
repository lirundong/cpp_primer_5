#pragma once
#ifndef _BOOK_STORE_H_
#define _BOOK_STORE_H_

#include <string>

/* CLASSES:
 */
class Quote {
public:
	Quote(const std::string &isbn_, double price_ = 0.0) :
		isbn(isbn_), price(price_) { };

	~Quote() { }
	// elements:
	std::string isbn;
	double price;
	// functions:
	virtual const double net_price(std::size_t n) const {
		return price * n;
	}

	virtual int debug(std::ostream &os) const {
		os << "isbn: " << isbn << std::endl
			<< "price: " << price << std::endl;
		return 0;
	}
};

class BulkQuote : public Quote {
public:
	// friends:
	friend const double net_price(const Quote &q, std::size_t n);

	// class-methods:
	BulkQuote(const std::string &isbn_, double price_ = 0.0,
		std::size_t thre = 0, double rate = 0.0) :
		Quote(isbn_, price_), _thre(thre), _rate(rate) { }

	~BulkQuote() { }

	const double net_price(std::size_t n) const override {
		return (n > _thre ? (n * price * _rate) : (n * price));
	}

	int debug(std::ostream &os) const override {
		os << "isbn: " << isbn << std::endl
			<< "price: " << price << std::endl
			<< "threshold: " << _thre << std::endl
			<< "rate: " << _rate << std::endl;
		return 0;
	}

protected:
	std::size_t _thre;
	double _rate;
};

/* FUNCTIONS:
 */
inline const double net_price(const Quote &q, std::size_t n) {
	return q.net_price(n);
}

#endif // !_BOOK_STORE_H_
