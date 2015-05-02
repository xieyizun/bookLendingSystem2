#include "Record.h"

Record::Record(): price(0.0), borrowTime(0), completed(false) {}

Record::Record(int recordID_, std::string bookName_, int bookID_, int lenderID_, int borrowerID_,
			double price_, int borrowTime_, bool completed_ = false):
			recordID(recordID_), bookName(bookName_), bookID(bookID_), lenderID(lenderID_),borrowerID(borrowerID_),
			price(price_), borrowTime(borrowTime_), completed(completed_) { }

bool Record::operator==(const Record &other) {
	if (recordID == other.recordID && bookName.compare(other.bookName) == 0 && 
		bookID == other.bookID && lenderID == other.lenderID && borrowerID == other.borrowerID &&
		completed == other.completed ) {
		return true;
	}
	return false;
}

int Record::getRecordID() const {
	return recordID;
}

std::string Record::getBookName() const {
	return bookName;
}
int Record::getBookID() const {
	return bookID;
}

int Record::getLenderID() const {
	return lenderID;
}

int Record::getBorrowerID() const {
	return borrowerID;
}

double Record::getPrice() const {
	return price;
}

int Record::getBorrowTime() const {
	return borrowTime;
}

bool Record::getCompleted() const {
	return completed;
}

void Record::setCompleted() {
	this->completed = true;
}