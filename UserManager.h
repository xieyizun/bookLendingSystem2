#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include <vector>
#include <algorithm>

class UserManager {
	public:
		~UserManager();
		static UserManager *getInstance(void);
		void initUsers(const std::vector<User> &users);
		User *findUserByName(std::string userName);
		void createUser(int userID, std::string userName, std::string userPassword, std::string userEmail,
			std::string userPhone, std::string userAddress, double userMoney);
		bool deleteUser(const User& user);
		void updateUserName(User &user, const std::string &newName);
		void updateUserPassword(User& user, const std::string &newPassword);
		void updateUserEmail(User& user, const std::string &newEmail);
		void updateUserPhone(User& user, const std::string &newPhone);
		void updateUserAddress(User& user, const std::string &newAddress);
		void updateUserMoney(User& user, double money);
		
		std::vector<User> listAllUsers(void);

	private:
		UserManager();
		UserManager(const UserManager&);
		UserManager& operator=(const UserManager&);

		std::vector<User> users;
		static bool hasInstance;
		static UserManager *instance;
};

#endif
