#include <iostream>
#include "UserManager.h" 

bool UserManager::hasInstance = false;
UserManager* UserManager::instance = NULL;

UserManager::UserManager() {}

UserManager::~UserManager() {
	if (instance != NULL) {
		delete instance;
	}
	hasInstance = false;
}

UserManager* UserManager::getInstance() {
	if (instance == NULL) {
		instance = new UserManager();
		hasInstance = true;
	}
	return instance;
}

void UserManager::initUsers(const std::vector<User> &users_) {
	users.clear();
	std::vector<User>::const_iterator iter_ = users_.begin();
	while (iter_ != users_.end()) {
		users.push_back(*iter_++);
	}
}

User* UserManager::findUserByName(std::string userName) {
	std::vector<User>::iterator iter = users.begin();
	while (iter != users.end()) {
		if (userName.compare(iter->getName()) == 0) {
			return &*iter; //*****
		}
		iter++;
	}
	return NULL;
}

void UserManager::createUser(int userID, std::string userName, std::string userPassword, std::string userEmail,
			std::string userPhone, std::string userAddress, double userMoney) {
	User newUser(userID, userName, userPassword, userEmail, userPhone,
				 userAddress, userMoney);
	users.push_back(newUser);
}

bool UserManager::deleteUser(const User& user) {
	std::vector<User>::iterator iter = find(users.begin(), users.end(), user);
	if (iter != users.end()) {
		users.erase(iter);
		return true;
	}
	return false;
}

void UserManager::updateUserName(User &user, const std::string &newName) {
	user.setName(newName);
}

void UserManager::updateUserPassword(User& user, const std::string &newPassword) {
	user.setPassword(newPassword);
}

void UserManager::updateUserEmail(User& user, const std::string &newEmail) {
	user.setEmail(newEmail);
}

void UserManager::updateUserPhone(User& user, const std::string &newPhone) {
	user.setPhone(newPhone);
}

void UserManager::updateUserAddress(User& user, const std::string &newAddress) {
	user.setAddress(newAddress);
}

void UserManager::updateUserMoney(User &user, double money) {
	user.setMoney(money);
}

std::vector<User> UserManager::listAllUsers() {
	return users;
}