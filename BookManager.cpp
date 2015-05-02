#include "BookManager.h"
#include <algorithm>

bool BookManager::hasInstance = false;
BookManager* BookManager::instance = NULL;

BookManager::BookManager() {}
BookManager::~BookManager() {
	if (instance != NULL) {
		delete instance;
	}
	hasInstance = false;
}

BookManager* BookManager::getInstance() {
	if (instance == NULL) {
		instance = new BookManager();
		hasInstance = true;
	}
	return instance;
}

void BookManager::initBooks(const std::multimap<std::string, Book>& books) {
	this->books.clear();
	this->books.insert(books.begin(), books.end());
}

void BookManager::initBooks2(const std::multimap<int, Book>& books2) {
	this->books2.clear();
	this->books2.insert(books2.begin(), books2.end());
}

void BookManager::addBook(int bookID, std::string bookName, std::string owerName, int ownerID, double price) {
	this->books.insert(make_pair(bookName, Book(bookID, bookName, owerName, ownerID, price, true)));
	this->books2.insert(std::make_pair(ownerID, Book(bookID, bookName, owerName, ownerID, price, true)));
}

bool BookManager::deleteBook(std::string ownerName, std::string bookName) {
	std::multimap<std::string, Book>::iterator beg = this->books.lower_bound(bookName);
	std::multimap<std::string, Book>::iterator end = this->books.upper_bound(bookName);
	while (beg != end) {
		if (ownerName.compare(beg->second.getOwnerName()) == 0) {
			int ownerID = (beg->second).getOwnerID();
			std::multimap<int, Book>::iterator beg2 = this->books2.lower_bound(ownerID);
			std::multimap<int, Book>::iterator end2 = this->books2.upper_bound(ownerID);

			while (beg2 != end2) {
				if (bookName.compare((beg2->second).getName()) == 0) {
					books2.erase(beg2);
					break;
				}
				beg2++;
			}
			
			books.erase(beg);
			return true;
		} 
		beg++;
	}
	return false;
}

void BookManager::updateBookState(Book &book) {
	if (book.getState() == true)
		book.setState(false);
	else
		book.setState(true);
}

std::vector<Book*> BookManager::searchBook(std::string bookName) {
	std::multimap<std::string, Book>::iterator beg = this->books.lower_bound(bookName);
	std::multimap<std::string, Book>::iterator end = this->books.upper_bound(bookName);
	std::vector<Book*> result;
	while (beg != end) {
		result.push_back(&beg->second);
		beg++;
	}
	return result;
}

std::vector<Book*> BookManager::searchBookByUserID(int userID) {
	std::multimap<int, Book>::iterator beg = this->books2.lower_bound(userID);
	std::multimap<int, Book>::iterator end = this->books2.upper_bound(userID);
	std::vector<Book*> result;
	while (beg != end) {
		result.push_back(&beg->second);
		beg++;
	}
	return result;
}