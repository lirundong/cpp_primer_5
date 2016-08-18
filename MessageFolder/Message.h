#pragma once
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <memory>
#include <set>
#include <string>
#include <iostream>

/*********************
 * Clacesses
 *********************/

class Folder;
class Message {
	friend class Folder;
	friend void swap(Message &lm, Message&rm);
public:
	Message(const std::string &str = " ");
	Message(Message &);
	~Message();
	// operators
	Message& operator=(const Message&);
	// save to Folder or delete from Folder
	void save(Folder &);
	void remove(Folder &);
	// print result
	std::ostream &info(std::ostream &os = std::cout);
	std::string *content() const { return _content; }

private:
	std::set<Folder*> _folders;
	std::string *_content;
	// method functions:
	void add_to_Folder(const Message&);  // called when copy a Message
	void remove_from_Folder();
};

class Folder {
public:
	Folder();
	~Folder();
	void addMsg(Message*);
	void remMsg(Message*);
	std::size_t idx() const { return _idx; }
	// print result
	std::ostream &info(std::ostream &os = std::cout);

private:
	std::set<Message*> _msg;
	std::size_t _idx;
	static std::size_t _idxBase;
};

/*********************
 * Functions
 *********************/
// Message::
Message::Message(const std::string &str):
	_content(new std::string(str)) { }

Message::Message(Message &m):
	_folders(m._folders), 
	_content(new std::string(*m._content)) {
	add_to_Folder(m);
}

Message::~Message() {
	remove_from_Folder();
	delete _content;
}

void Message::save(Folder &f) {
	_folders.insert(&f);  // use & to get ptr
	f.addMsg(this);
}

void Message::remove(Folder &f) {
	_folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folder(const Message &m) {
	/* this function is called when *this copy from m
	 * *this is a value-like instant, so it must be in the
	 * Folder(s) which m belongs to
	 */
	for (auto f : m._folders) {
		f->addMsg(this);
	}
}

void Message::remove_from_Folder() {
	/* this function is called when ~Message() being called
	 * make sure that Folders won't contain *this any more
	 */
	for (auto f : _folders) {
		f->remMsg(this);
	}
}

Message& Message::operator=(const Message &m) {
	remove_from_Folder();
	delete _content;
	_content = new std::string(*m._content);
	_folders = m._folders;
	add_to_Folder(m);
	return *this;
}

std::ostream& Message::info(std::ostream &os) {
	os << "Message:" << std::endl
		<< "Content: " << *_content << std::endl
		<< "Folders: ";
	for (auto f : _folders)
		os << f->idx() << ", ";
	os << "." << std::endl;
	return os;
}

// Use Message& as argument(s):
void swap(Message &lm, Message&rm) {
	using std::swap;
	for (auto f : lm._folders)
		f->remMsg(&lm);
	for (auto f : rm._folders)
		f->remMsg(&rm);
	swap(lm._content, rm._content);
	swap(lm._folders, rm._folders);
	for (auto f : lm._folders)
		f->addMsg(&lm);
	for (auto f : rm._folders)
		f->addMsg(&rm);
}

// Folder::
// initialize static _idxBase
std::size_t Folder::_idxBase = 0;

Folder::Folder():_idx(++_idxBase) {}

Folder::~Folder() {}

void Folder::addMsg(Message *m) {
	_msg.insert(m);
}

void Folder::remMsg(Message *m) {
	_msg.erase(m);
}

std::ostream& Folder::info(std::ostream &os) {
	os << "Folder:" << std::endl
		<< "Index: " << _idx << std::endl
		<< "Messages: " << std::endl;
	for (auto m : _msg)
		os << "\t" << *(m->content()) << std::endl;
	return os;
}

#endif // !_MESSAGE_H_
