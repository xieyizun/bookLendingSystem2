#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
	public:
		Book();
		Book(int bookID, std::string bookName, std::string ownerName_, int ownerID, double price_, bool state_);
		bool operator==(const Book &other);

		int getBookID() const;
		
		std::string getName() const;
		void setName(std::string name);

		double getPrice() const;
		void setPrice(double price);

		std::string getOwnerName() const;
		void setOwnerName(std::string ownerName);

		int getOwnerID() const;

		bool getState() const;
		void setState(bool state);

	private:
		int bookID;
		std::string bookName;	
		std::string ownerName;
		int ownerID;
		double price;
		bool state;
};

#endif
