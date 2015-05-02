#include "User.h"

User::User(): money(0.0) {}

User::User(int userID, std::string userName, std::string userPassword, std::string userEmail, 
		std::string userPhone, std::string userAddress, double money) :
		userID(userID), name(userName), password(userPassword), email(userEmail),
		phone(userPhone), address(userAddress), money(money) { }

bool User::operator==(const User &other) {
	if (name.compare(other.name) == 0)
		return true;
	return false;
}

int User::getUserID() const {
	return userID;
}

std::string User::getName() const {
	return name;
}
void User::setName(std::string name) {
	this->name = name;
}

std::string User::getPassword() const {
	return password;
}
void User::setPassword(std::string password) {
	this->password = password;
}

std::string User::getEmail() const {
	return email;
}
void User::setEmail(std::string email) {
	this->email = email;
}

std::string User::getPhone() const {
	return phone;
}

void User::setPhone(std::string phone) {
	this->phone = phone;
}

std::string User::getAddress() const {
	return address;
}
void User::setAddress(std::string address) {
	this->address = address;
}

double User::getMoney() const {
	return money;
}
void User::setMoney(double money) {
	this->money = money;
}