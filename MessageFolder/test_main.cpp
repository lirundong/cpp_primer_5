#include "Message.h"

int main(int argc, char *argv[]) {
	Folder good, bad;  // BUG HERE: if Folder decalare after Message,
					   // then ~Floder() will happen before ~Message()
					   // this will cause a fatal error
	Message m1("good news!"),
		m2("Rio 2016 informations"),
		m3("not a good news"),
		m4("let's play Over Watch!"),
		m5("I don't know good or bad");

	m1.save(good);
	m2.save(good);
	m3.save(bad);
	m4.save(good);
	m5.save(bad);

	std::cout << "Before swap" << std::endl;
	good.info();
	bad.info();

	swap(m3, m4);

	std::cout << "After swap" << std::endl;
	good.info();
	bad.info();

	return 0;
}
