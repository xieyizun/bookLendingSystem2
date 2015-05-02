#ifndef BOOKSYSTEMSERVICE_H
#define BOOKSYSTEMSERVICE_H
#include <string>
#include "User.h"
#include "SessionController.h"

class BookSystemService {
	public:
		BookSystemService();
		~BookSystemService();

		int welcome();
		void startService();
		void stopService();
		bool logInAccount();
		bool registerAccount();
		void accountOnLine();
	private:
		int functionSelection();
		void bookSearchAndLend();
		void bookReturn();
		void viewMyBorrowerRecords();
		void viewMyLenderRecords();
		void viewMyBooks();
		void viewAllUsers();
		void addBook();
		void addMyAccountMoney();
		void deleteMybook();
		void deleteMyRecord();
		void viewMyAccount();
		void modifyMyAccount();
		bool deleteMyAccount();
		SessionController *session;
		User *currentUser;
};
#endif