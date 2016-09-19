#include <iostream>
#include "Bookstore.h"

int main() {
	Quote book1("123-1", 15.99);
	BulkQuote bookSale1("123-2", 16.99, 5, 0.4);

	std::cout << "Book1 for 10:\t" << net_price(book1, 10) << std::endl
		<< "Book on sale for 10:\t" << net_price(bookSale1, 10) << std::endl;

#ifdef _DEBUG
	book1.debug(std::cout);
	bookSale1.debug(std::cout);
#endif // _DEBUG


	return 0;
}
