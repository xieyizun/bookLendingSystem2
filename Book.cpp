#include "Book.h"

Book::Book(): price(0.0), state(true) {}

Book::Book(int bookID, std::string bookName,  std::string ownerName_, int ownerID_, double price_, bool state_) :
	bookID(bookID), bookName(bookName), ownerName(ownerName_), ownerID(ownerID_), price(price_), state(state_) {}

bool Book::operator==(const Book &other) {
	if (bookName.compare(other.bookName) == 0 && ownerName.compare(other.ownerName) == 0) {
		return true;
	}
	return false;
}

int Book::getBookID() const {
	return bookID;
}

std::string Book::getName() const {
	return bookName;
}
void Book::setName(std::string name) {
	this->bookName = name;
}

double Book::getPrice() const {
	return price;
}
void Book::setPrice(double price) {
	this->price = price;
}

std::string Book::getOwnerName() const {
	return ownerName;
}
void Book::setOwnerName(std::string ownerName) {
	this->ownerName = ownerName;
}

int Book::getOwnerID() const {
	return ownerID;
}

bool Book::getState() const{
	return state;
}
void Book::setState(bool state) {
	this->state = state;
}