#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <map>
#include <vector>
#include "Book.h"

class BookManager {
	public:
		~BookManager();
		static BookManager *getInstance(void);

		void initBooks(const std::multimap<std::string, Book> &books);
		void initBooks2(const std::multimap<int, Book> &books2);
		void addBook(int bookID, std::string bookName, std::string ownerName, int ownerID, double price);
		bool deleteBook(std::string ownerName, std::string bookName);
		void updateBookState(Book &book);
		std::vector<Book*> searchBook(std::string bookName);//返回指针为难点,目的为在借还书时修改书的状态
		std::vector<Book*> searchBookByUserID(int userID);
	private:
		BookManager();
		BookManager(const BookManager&);
		BookManager& operator=(const BookManager&);

		std::multimap<std::string, Book> books;
		std::multimap<int, Book> books2;

		static bool hasInstance;
		static BookManager *instance;
};

#endif
