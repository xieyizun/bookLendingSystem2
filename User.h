#ifndef USER_H
#define USER_H

#include <string>

class User {
	public:
		User();
		User(int userID, std::string userName, std::string userPassword, std::string userEmail, 
			 std::string userPhone, std::string userAddress, double money);
		~User() { }

		bool operator==(const User &other);
		
		int getUserID() const;

		std::string getName() const;
		void setName(std::string name);

		std::string getPassword() const;
		void setPassword(std::string password);

		std::string getEmail() const;
		void setEmail(std::string email);

		std::string getPhone() const;
		void setPhone(std::string phone);

		std::string getAddress() const;
		void setAddress(std::string address);

		double getMoney() const;
		void setMoney(double money);
		
	private:
		int userID;
		std::string name;
		std::string password;
		std::string email;
		std::string phone;
		std::string address;
		double money;
};

#endif