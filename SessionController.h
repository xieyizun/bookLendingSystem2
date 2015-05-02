#ifndef SESSIONCONTROLLER_H
#define SESSIONCONTROLLER_H

#include <string>
#include <vector>
#include "UserManager.h"
#include "BookManager.h"
#include "RecordManager.h"
#include "mysql.h"

class SessionController {
	public:
		SessionController();

		~SessionController();
		
		User* userLogIn(const std::string &userName, const std::string &password);
		bool userExist(const std::string &userName);
		bool userRegister(std::string userName, std::string userPassword, std::string userEmail,
						  std::string userPhone, std::string userAddress, double money);
		bool addUserMoney(User &user, double money);
		bool modifyUserInfo(User &user, int select, const std::string &content);

		std::vector<User> listAllUsers();

		bool addBook(std::string bookName, User &owner, double price);
		std::vector<Book*> queryBook(std::string bookName);
		bool lendBook(User &borrower, Book &book, int borrowTime);
		bool returnBook(User &borrower, Record &record);
		std::vector<Book*> listAllMyBooks(int userID);
		std::vector<Record*> listAllMyRecords(int userID);
		std::vector<Record*> listMyBorrowerRecords(int userID);
		std::vector<Record*> listMyLenderRecords(int userID);
		
		bool deleteBook(const User &owner, const Book &book);
		bool deleteRecord(const User &user, const Record &record);
		bool deleteUser(const User& user);
		
		void startBookSystem();
		void quitBookSystem();
		
	private:
		UserManager *userManager;
		BookManager *bookManager;
		RecordManager *recordManager;

		MYSQL *conn;
		MYSQL_STMT *stmt; //mysql预处理语句结构
		MYSQL_BIND userB[7]; //user
		MYSQL_BIND bookB[6]; //book
		MYSQL_BIND recordB[8]; //record

		MYSQL_BIND insertR[7]; //register a new user
		MYSQL_BIND newUser[6];//register
		MYSQL_BIND userInfo[3];//update user info
		MYSQL_BIND rBook[3];//return book

		std::vector<User> getAllUsersFromMySQL();
		std::vector<Book> getAllBooksFromMySQL();
		std::vector<Record> getAllRecordFromMySQL();
};

#endif
