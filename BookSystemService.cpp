#include <iostream>
#include <string>
#include <iomanip>
#include <map>

#include "BookSystemService.h"
#include "./chatSpace/Client.cpp"

BookSystemService::BookSystemService() {
	session = new SessionController();
	currentUser = new User();
}

BookSystemService::~BookSystemService() {
	if (session != NULL) {
		delete session;
	}
	/*不需要
	if (currentUser != NULL)
		delete currentUser;
	*/
}

int BookSystemService::welcome() {
	std::cout << std::endl;
	std::cout << " *************************************************************" << std::endl;
	std::cout << " *                 欢迎来到图书借阅管理系统                  *" << std::endl;
	std::cout << " *************************************************************" << std::endl;
	std::cout << " 1.登陆 2.注册 3.退出 : ";
	int select;
	std::cin >> select;
	return select;
}

void BookSystemService::startService() {
	session->startBookSystem();
}
void BookSystemService::stopService() {
	session->quitBookSystem();
}

bool BookSystemService::logInAccount() {
	std::cout << " 请输入用户名: ";
	std::string name, password;
	std::cin.ignore();//或者getline,使用此句的目的是忽略掉之前的换行符,因为getline一读到换行符就退出
	std::getline(std::cin, name);
	//std::cin >> name;

	std::cout << " 请输入密码: ";
	//std::cin.ignore();
	//std::getline(std::cin, password);
	std::cin >> password;

	currentUser = session->userLogIn(name, password);

	if (currentUser == NULL) {
		std::cout << "\n 账户不存在,或者用户名或密码错误!" << std::endl;
		return false;
	} else {
		return true;
	}
}

bool BookSystemService::registerAccount() {
	char ys;
	std::cout << "\n 说明: 注册账号时, 您需要上传5本或以上的书籍到该图书借阅系统." << std::endl;
	std::cout << "\n 确定注册账号?(y/n): ";
	std::cin >> ys;
	if (ys == 'y') {
		std::string name, password, email, phone, address;
	  	while (true) {	
			std::cout << "\n 请输入您的用户名: ";
			std::cin >> name;
			std::cout << " 请输入您的用户密码: ";
			std::cin >> password;
			std::cout << " 请输入您的邮箱: ";
			std::cin >> email;
			std::cout << " 请输入您的电话号码: ";
			std::cin >> phone;
			std::cout << " 请输入您的地址: ";
			std::cin.ignore();
			std::getline(std::cin, address);

			while (session->userExist(name)) {
				std::cout << " 此用户名已经存在, 请重新输入一个新用户名: ";
				std::cin >> name;
			}
			std::cout << "\n 确认以上用户信息?(y/n): ";
			std::cin >> ys;
			if (ys == 'y')
				break;
		}

		std::cout << "\n\n 请上传5本或以上书籍:" << std::endl;
		std::map<std::string, double> books;
		std::vector<std::string> bookNames;
		int count = 0;
		int number = 0;
		while (count < 5) {
			std::cout << " 请输入书名: ";
			std::string bookName;
			std::cin.ignore();
			std::getline(std::cin, bookName);
			std::cout << " 请设定该书价格: ";
			double price;
			std::cin >> price;

			if (books.count(bookName)) {
				std::cout << "\n 该书已经上传过了,每本书只能上传一次! 请重新上传." << std::endl;
				continue;
			} else {
				books[bookName] = price;
				bookNames.push_back(bookName);
				count++;
				number++;
				std::cout << "\n 当前已经添加了: " << number << "本书." << std::endl;
				if (count == 5) {
					std::cout << "\n 继续添加书籍?(y/n): ";
					std::cin >> ys;
					if (ys == 'y') {
						count--;
					} else {
						break;
					}
				}
			}
		}
		if (session->userRegister(name, password, email, phone, address, 0)) {
			currentUser = session->userLogIn(name, password);
			
			for (int i = 0; i < bookNames.size(); i++) {
				if (!session->addBook(bookNames[i], *currentUser, books[bookNames[i]])) {
					std::cout << "\n 上传书籍: "<< bookNames[i] << " 失败!" << std::endl;
					return false;
				}
			}
			std::cout << "\n 用户注册成功!" << std::endl;
			return true;
		} else {
			std::cout << "\n 提交用户注册信息失败!" << std::endl;
			return false;
		}
	} else {
		return false;
	}

}

int BookSystemService::functionSelection() {	
	std::cout << std::left << std::setw(43) << " 1. 搜索并借阅图书";
	std::cout << std::left << " 8. 添加书籍" << std::endl;

	std::cout << std::left << std::setw(40) << " 2. 归还图书";
	std::cout << std::left << " 9. 充值" << std::endl;

	std::cout << std::left << std::setw(44) << " 3. 查看我的借书记录";
	std::cout << std::left << " 10.删除书籍" << std::endl;

	std::cout << std::left << std::setw(45) << " 4. 查看我的书被借记录";
	std::cout << std::left << " 11.删除图书借阅记录" << std::endl;

	std::cout << std::left << std::setw(42) << " 5. 查看我的书籍";
	std::cout << std::left << " 12.查看我的用户资料" << std::endl;

	std::cout << std::left << std::setw(42) << " 6. 查看所有用户";
	std::cout << std::left << " 13.修改我的用户资料" << std::endl;

	std::cout << std::left << std::setw(40) << " 7. 退出系统";
	std::cout << std::left << " 14.注销我的个人用户" << std::endl;

	//登陆图书交流社区
	std::cout << "\n 15.登陆图书交流社区" << std::endl;
	
	std::cout << "-------------------------------------------------------------" << std::endl;
	std::cout << "\n 请选择您需要进行的操作: ";
	int select;
	std::cin >> select;
	return select;
}

void BookSystemService::bookSearchAndLend()  {
	std::cout << " 请输入完整书名: ";
	std::string bookName;
	std::cin.ignore(); //有问题
	std::getline(std::cin, bookName);
	
	std::vector<Book*> books = session->queryBook(bookName);
	std::cout << "\n 该书可借列表: " << std::endl;
	std::cout << std::setw(10) << std::left << " 序号" << std::setw(20) << std::left << " 书名" << std::setw(20) << std::left << "拥有者";
	std::cout << std::setw(18) << std::left << " 价格" << std::endl << " ";
	int num = 1;
	std::map<int, int> indexs;//保存可借书的下标
	for (int i = 0; i < books.size(); i++) {
		if (books[i]->getState() == true) {
			indexs[num] = i;
			std::cout << std::setw(7) << std::left << num++ << std::setw(18) << std::left << " "+books[i]->getName() << std::setw(18) << std::left << books[i]->getOwnerName();
			std::cout << std::setw(18) << std::left << books[i]->getPrice();
			std::cout << std::endl << " ";
		}
	}
	std::cout << std::endl;

  	if (num > 1) {
	  std::cout << " 请选择您需要借阅的序号: ";
	  int number;
	  char ys;
	  while (std::cin >> number) {
		if (number <= 0 || number >= num) {
			std::cout << " 序号不在范围内,重新输入?(y/n): ";		
			std::cin >> ys;
			if (ys == 'y') {
				std::cout << " 请选择您需要借阅的序号: ";
				continue;
			} else 
				break;
		} else {
			if (books[indexs[number]]->getState() == 0) {
				std::cout << " 书籍已借出, 暂时无法借阅!" << std::endl;
				std::cout << " 重新选择序号?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << " 请选择您需要借阅的序号: ";
					continue;
				} else {
					break;
				}
			} else if (books[indexs[number]]->getOwnerID()==currentUser->getUserID()) {
				std::cout << " 您不能借阅自己的图书!" << std::endl;
				std::cout << " 重新选择序号?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << " 请选择您需要借阅的序号: ";
					continue;
				} else {
					break;
				}
			} else {
				std::cout << " 确定借阅该书籍(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << " 请选择借阅时间(天数): ";
					int borrowTime;
					std::cin >> borrowTime;
					if (session->lendBook(*currentUser, *books[number-1], borrowTime)) {
						std::cout << " 借阅成功!" << std::endl;
					} else {
						std::cout << " 借阅失败!" << std::endl;
					}
					break;
				} else {
					std::cout << " 重新选择序号?(y/n): ";
					std::cin >> ys;
					if (ys == 'y') {
						std::cout << " 请选择您需要借阅的序号: ";
						continue;
					} else {
						break;
					}
				}
			}
		}
	  }
	} else {
		if (books.size() == 0)
			std::cout << " 您搜索的书籍不存在!" << std::endl;
		else if (num == 1) 
			std::cout << " 您搜索的书籍已被借完, 暂时无法借阅!" << std::endl;
	}
}

void BookSystemService::bookReturn() {
	std::cout << "\n 以下为您所借未还的书籍:\n" << std::endl;
	std::vector<Record*> myBorrowerRecords(session->listMyBorrowerRecords(currentUser->getUserID()));
	std::cout << std::setw(10) << std::left << " 序号" << std::setw(20) << std::left << "书名" << std::setw(20) << std::left << "拥有者ID";
	std::cout << std::setw(18) << std::left << "价格" << std::setw(18) << std::left << "借用天数" << std::endl << " ";
	
	int number = 1;
	std::map<int, int> nums;//保存未还书的下标
	for (int i = 0; i < myBorrowerRecords.size(); i++) {
		if (myBorrowerRecords[i]->getCompleted() == false) {
			nums[number] = i;
			std::cout << std::setw(6) << std::left << number++ << std::setw(21) << std::left << myBorrowerRecords[i]->getBookName();
			std::cout << std::setw(15) << std::left << myBorrowerRecords[i]->getLenderID();
			std::cout << std::setw(18) << std::left << myBorrowerRecords[i]->getPrice() << std::setw(10) << std::left << myBorrowerRecords[i]->getBorrowTime();
			std::cout << std::endl << " "; 
		}
	}
	if (number > 1) {
		std::cout << "请选择您需要归还的书的序号: ";
		int select; 
		char ys;
		while (std::cin >> select) {
			if (select <= 0 || select >= number) {
				std::cout << " 您输入的序号超出了序号范围, 重新输入?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << " 请选择您需要还的书的序号: ";
					continue;
				} else {
					break;
				}
			} else {
				std::cout << " 确认归还?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					if (myBorrowerRecords[nums[select]]->getCompleted() == false && session->returnBook(*currentUser, *myBorrowerRecords[nums[select]])) {
						std::cout << " 归还成功! 押金: " << myBorrowerRecords[nums[select]]->getPrice() << "元, 已成功归还到您的账户."<< std::endl;
						std::cout << " 您当前的账户余额为: " << currentUser->getMoney() << std::endl;
						break;
					} else {
						if (myBorrowerRecords[nums[select]]->getCompleted() == true) {
							std::cout << " 书籍已归还, 归还失败!" << std::endl;
						} else {
							std::cout << " 归还失败!" << std::endl;
						}
						std::cout << " 重新选择需要归还的书的序号?(y/n): ";
						std::cin >> ys;
						if (ys == 'y') {
							std::cout << " 请选择您需要还的书的序号: ";
							continue;
						} else {
							break;
						}
					}
				} else {
					std::cout << " 重新选择需要归还的书的序号?(y/n): ";
					std::cin >> ys;
					if (ys == 'y') {
						std::cout << " 请选择您需要还的书的序号: ";
						continue;
					} else {
						break;
					}
				}
			}
		}	
	} else {
		std::cout << "您当前没有未还书籍!" << std::endl;
	}
}

void BookSystemService::viewMyBorrowerRecords() {
	std::vector<Record*> myBorrowerRecords(session->listMyBorrowerRecords(currentUser->getUserID()));
	if (myBorrowerRecords.size() > 0) {
		std::cout << "\n 以下为您的借书记录: " << std::endl;
		std::cout << std::setw(10) << std::left << " 序号" << std::setw(20) << std::left << "书名" << std::setw(15) << std::left << "拥有者ID";
		std::cout << std::setw(15) << std::left << "价格" << std::setw(18) << std::left << "借用天数" << "是否已归还"<< std::endl << " ";
	
		std::string ret;
		for (int i = 0; i < myBorrowerRecords.size(); i++) {
			if (myBorrowerRecords[i]->getCompleted() == false) 
				ret = "否";
			else
				ret = "是";
			std::cout << std::setw(6) << std::left << i+1 << std::setw(21) << std::left << myBorrowerRecords[i]->getBookName();
			std::cout << std::setw(10) << std::left << myBorrowerRecords[i]->getLenderID();
			std::cout << std::setw(15) << std::left << myBorrowerRecords[i]->getPrice() << std::setw(15) << std::left << myBorrowerRecords[i]->getBorrowTime();
			std::cout << ret;
			std::cout << std::endl << " "; 
		}
		std::cout << std::endl;
	} else {
		std::cout << "\n 您当前还没有借过书." << std::endl;
	}
}

void BookSystemService::viewMyLenderRecords() {
	std::vector<Record*> myLenderRecords(session->listMyLenderRecords(currentUser->getUserID()));
    if (myLenderRecords.size() > 0) {
    	std::cout << "\n 以下为您的书的借出记录: " << std::endl;
		std::cout << std::setw(10) << std::left << " 序号" << std::setw(20) << std::left << "书名" << std::setw(15) << std::left << "借书者ID";
		std::cout << std::setw(15) << std::left << "价格" << std::setw(18) << std::left << "借用天数" << "是否已归还"<< std::endl << " ";
	
		std::string ret;
		for (int i = 0; i < myLenderRecords.size(); i++) {
			if (myLenderRecords[i]->getCompleted() == false) 
				ret = "否";
			else
				ret = "是";
			std::cout << std::setw(6) << std::left << i+1 << std::setw(21) << std::left << myLenderRecords[i]->getBookName();
			std::cout << std::setw(10) << std::left << myLenderRecords[i]->getBorrowerID();
			std::cout << std::setw(15) << std::left << myLenderRecords[i]->getPrice() << std::setw(15) << std::left << myLenderRecords[i]->getBorrowTime();
			std::cout << ret;
			std::cout << std::endl << " "; 
		}
		std::cout << std::endl;
	} else {
		std::cout << "\n 您当前没有书籍被借出." << std::endl;
	}
}

void BookSystemService::viewMyBooks() {
	std::vector<Book*> books(session->listAllMyBooks(currentUser->getUserID()));
	if (books.size() > 0) {
		std::cout << "\n 您上传的书籍列表: " << std::endl;
		std::cout << std::setw(18) << std::left << " 序号" << std::setw(20) << std::left << "书名";
		std::cout << std::setw(20) << std::left << "价格" << std::endl << " ";
		for (int i = 0; i < books.size(); i++) {
			std::cout << std::setw(15) << std::left << i+1 << std::setw(17) << std::left << books[i]->getName();
			std::cout << std::setw(16) << std::left << books[i]->getPrice();
			std::cout << std::endl << " ";
		}
		std::cout << std::endl;
	} else {
		std::cout << "\n 您当前未上传书籍." << std::endl;
	}
}

void BookSystemService::viewAllUsers() {
	std::vector<User> users(session->listAllUsers());
	if (users.size() > 0) {
		std::cout << "\n 当前系统的所有注册用户列表:" << std::endl;
		std::cout << std::setw(18) << std::left << " 序号" << std::setw(20) << std::left << "用户名";
		std::cout << std::setw(20) << std::left << "用户邮箱" << "电话号码" << std::endl << " ";
		for (int i = 0; i < users.size(); i++) {
			std::cout << std::setw(15) << std::left << i+1 << std::setw(17) << std::left << users[i].getName();
			std::cout << std::setw(16) << std::left << users[i].getEmail() << users[i].getPhone();
			std::cout << std::endl << " ";
		}
		std::cout << std::endl;
	} else {
		std::cout << "\n 当前系统还没有用户." << std::endl;
	}
}

void BookSystemService::addBook() {
	std::cout << "\n 请输入您要添加的书的名字: ";
	std::cin.ignore();
	std::string name;
	std::getline(std::cin, name);

	std::cout << "\n 请输入您要添加的书的价格: ";
	double price;
	std::cin >> price;
	char ys;
	std::cout << " 确认添加?(y/n): ";
	std::cin >> ys;
	if (ys == 'y') {
		if (session->addBook(name, *currentUser, price)) {
			std::cout << " 添加成功!" << std::endl;
			std::cout << std::setw(20) << std::left << " 书名" << "价格" << std::endl << " ";
			std::cout << std::setw(18) << std::left << name << price << std::endl;
		} else {
			std::cout << " 添加失败!" << std::endl;
		}
	}
}

void BookSystemService::addMyAccountMoney() {
	std::cout << "\n 请输入您需要充值的金额: ";
	double money;
	char ys;
	while (std::cin >> money) {
		if (money <= 0) {
			std::cout << " 您输入的金额不能小于等于0元, 重新输入?(y/n): ";
			std::cin >> ys;
			if (ys == 'y') {
				std::cout << "\n 请输入您需要充值的金额: ";
				continue;
			} else {
				break;
			}
		} else {
			std::cout << " 确认充值: " << money << "元?(y/n): ";
			std::cin >> ys;
			if (ys == 'y') {
				if (session->addUserMoney(*currentUser, money)) {
					std::cout << " 充值成功!" << std::endl;
					std::cout << " 您的当前账户余额为: " << currentUser->getMoney() << "元." << std::endl;
				} else {
					std::cout << " 充值失败!" << std::endl;
				}
				break;
			} else {
				std::cout << " 重新输入充值金额?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << "\n 请输入您需要充值的金额: ";
					continue;
				} else {
					break;
				}
			}
		}
	}

}

void BookSystemService::deleteMybook() {
	std::vector<Book*> books(session->listAllMyBooks(currentUser->getUserID()));
	if (books.size() == 0) {
		std::cout << "\n 您当前未上传书籍!" << std::endl;
	} else {
		std::cout << "\n 您当前上传的书籍列表:" << std::endl;
		std::cout << std::setw(18) << std::left << " 序号" << std::setw(20) << std::left << "书名";
		std::cout << std::setw(20) << std::left << "价格" << std::endl << " ";

		for (int i = 0; i < books.size(); i++) {
			std::cout << std::setw(15) << std::left << i+1 << std::setw(17) << std::left << books[i]->getName();
			std::cout << std::setw(16) << std::left << books[i]->getPrice();
			std::cout << std::endl << " ";
		}
		std::cout << std::endl;
		std::cout << " 请输入您需要删除的书的序号: ";
		int num;
		char ys;
		while (std::cin >> num) {
			if (num <= 0 || num > books.size()) {
				std::cout << " 您输入的序号超出了序号范围, 重新输入?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << " 请输入您需要删除的书的序号: ";
					continue;
				} else {
					break;
				}
			} else {
				std::cout << " 确认删除?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					if (session->deleteBook(*currentUser, *books[num-1])) {
						std::cout << " 删除成功!" << std::endl;
					} else {
						std::cout << " 该书您已借出,请等待归还后删除,删除失败!" << std::endl;
					}
					break;
				} else {
					std::cout << " 重新选择书的序号?(y/n): ";
					std::cin >> ys;
					if (ys == 'y') {
						std::cout << " 请输入您需要删除的书的序号: ";
						continue;
					} else {
						break;
					}
				}
			}
		}
	}
}

void BookSystemService::deleteMyRecord() {
	std::cout << "\n 请选择您需要删除的记录类型: 1.我的书借书的记录  2. 我借书的记录: ";
	int select;
	char ys;
	std::cin >> select;
	if (select == 1) {
	  viewMyLenderRecords();
	  std::vector<Record*> records(session->listMyLenderRecords(currentUser->getUserID()));
	  if (records.size() > 0) {
		 std::cout << " 请选择您要删除的记录的序号: ";
		 int num;
		 while (std::cin >> num) {
			if (num <= 0 || num > records.size()) {
				std::cout << " 您输入的序号超出了序号范围, 重新输入?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << " 请选择您要删除的记录的序号: ";
					continue;
				} else {
					break;
				}
			} else {
				if (records[num-1]->getCompleted() == false) {
					std::cout << " 借出的书仍未归还回来!该记录无法删除!" << std::endl;
					std::cout << " 重新选择记录序号?(y/n): ";
					std::cin >> ys;
					if (ys == 'y') {
						std::cout << " 请选择您要删除的记录的序号: ";
						continue;
					} else {
						break;
					}
				} else {
					std::cout << " 确认删除?(y/n): ";
					std::cin >> ys;
					if (ys == 'y') {
						if (session->deleteRecord(*currentUser, *records[num-1])) {
							std::cout << " 记录删除成功!" << std::endl;
						} else {
							std::cout << " 记录删除失败!" << std::endl;
						}
						break;
					} else {
						std::cout << " 重新选择记录序号?(y/n): ";
						std::cin >> ys;
						if (ys == 'y') {
							std::cout << " 请选择您要删除的记录的序号: ";
							continue;
						} else {
							break;
						}
					}
				}
			}
		  }
		}
	} else if (select == 2) {
	  viewMyBorrowerRecords();
	  std::vector<Record*> records(session->listMyBorrowerRecords(currentUser->getUserID()));
	  if (records.size() > 0) {	
		 std::cout << " 请选择您要删除的记录的序号: ";
		 int num;
		 while (std::cin >> num) {
			if (num <= 0 || num > records.size()) {
				std::cout << " 您输入的序号超出了序号范围, 重新输入?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << " 请选择您要删除的记录的序号: ";
					continue;
				} else {
					break;
				}
			} else {
				if (records[num-1]->getCompleted() == false) {
					std::cout << " 您所借书仍未归还给拥有者!该记录无法删除!" << std::endl;
					std::cout << " 重新选择记录序号?(y/n): ";
					std::cin >> ys;
					if (ys == 'y') {
						std::cout << " 请选择您要删除的记录的序号: ";
						continue;
					} else {
						break;
					}
				} else {
					std::cout << " 确认删除?(y/n): ";
					std::cin >> ys;
					if (ys == 'y') {
						if (session->deleteRecord(*currentUser, *records[num-1])) {
							std::cout << " 记录删除成功!" << std::endl;
						} else {
							std::cout << " 记录删除失败!" << std::endl;
						}
						break;
					} else {
						std::cout << " 重新选择记录序号?(y/n): ";
						std::cin >> ys;
						if (ys == 'y') {
							std::cout << " 请选择您要删除的记录的序号: ";
							continue;
						} else {
							break;
						}
					}
				}
			}
		 }
	 }
	}
}


void BookSystemService::viewMyAccount() {
	std::cout << "\n 您的个人信息:" << std::endl;
	std::cout << " 用户名: " << currentUser->getName() << std::endl;
	std::cout << " 用户密码: " << currentUser->getPassword() << std::endl;
	std::cout << " 邮箱: " << currentUser->getEmail() << std::endl;
	std::cout << " 电话号码: " << currentUser->getPhone() << std::endl;
	std::cout << " 地址: " << currentUser->getAddress() << std::endl;
	std::cout << " 余额: " << currentUser->getMoney() << "元." << std::endl;
}

void BookSystemService::modifyMyAccount() {
	std::cout << "\n 请选择您需要修改的信息: 1.用户名 2.用户密码 3.邮箱 4.电话号码 5.地址: ";
	int select;
	std::string content;
	char ys;
	while (std::cin >> select) {
		if (select <= 0 || select >= 6) {
			std::cout << " 您输入的序号超出了序号范围, 重新输入?(y/n): ";
			std::cin >> ys;
			if (ys == 'y') {
				std::cout << "\n 请选择您需要修改的信息: 1.用户名 2.用户密码 3.邮箱 4.电话号码 5.地址: ";
				continue;
			} else {
				break;
			}
		} else {
			std::string dowhat = " 请输入您的新";
			std::string check = " 确认修改?(y/n): ";
			switch(select) {
				case 1: {
					std::cout << dowhat << "用户名: ";
					std::cin.ignore();
					std::getline(std::cin, content);
					break;
				}
				case 2: {
					std::cout << dowhat << "密码: ";
					std::cin.ignore();
					std::getline(std::cin, content);
					break;
				}
				case 3: {
					std::cout << dowhat << "邮箱: ";
					std::cin.ignore();
					std::getline(std::cin, content);
					break;
				}
				case 4: {
					std::cout << dowhat << "电话号码: ";
					std::cin.ignore();
					std::getline(std::cin, content);
					break;
				}
				case 5: {
					std::cout << dowhat << "地址: ";
					std::cin.ignore();
					std::getline(std::cin, content);
					break;
				}
			}
			std::cout << check;
			std::cin >> ys;
			if (ys == 'y') {
				if (session->modifyUserInfo(*currentUser, select, content)) {
					std::cout << " 修改成功!" << std::endl;
					viewMyAccount();
				} else {
					std::cout << " 修改失败!" << std::endl;
				}
				break;
			} else {
				std::cout << " 重新选择修改项?(y/n): ";
				std::cin >> ys;
				if (ys == 'y') {
					std::cout << "\n 请选择您需要修改的信息: 1.用户名 2.用户密码 3.邮箱 4.电话号码 5.地址: ";
					continue;
				} else {
					break;
				}
			}
		}
	}
}

bool BookSystemService::deleteMyAccount() {
	std::cout << "\n 注意: 该操作会使得您的账户被注销, 以为需重新注册账户才能登陆系统!" << std::endl;
	std::cout << "\n 确认注销?(y/n): ";
	char ys;
	std::cin >> ys;
	if (ys == 'y') {
		if (session->deleteUser(*currentUser)) {
			std::cout << "\n 注销成功!" << std::endl;	
			return false;	//设置accountOnLine中的on值
		} else {
			std::cout << "\n 注销失败!" << std::endl;
			return true;
		}
	}
	return true;
}

void BookSystemService::accountOnLine() {
	std::cout << "\n 登陆成功!" << std::endl;
	std::cout << "-------------------------------------------------------------" << std::endl;
	bool on = true;
	while (on) {
	  std::cout << std::endl;
	  int select = functionSelection();
	  switch(select) {
		case 1: {
			while (true) {
				bookSearchAndLend();
				std::cout << " 继续搜索书籍(y/n): ";
				char ys;
				std::cin >> ys;
				if (ys == 'n')
					break; 
			}
			break;
		}
		case 2: {
			while (true) {
				bookReturn();
				std::cout << " 继续归还书籍(y/n): ";
				char ys;
				std::cin >> ys;
				if (ys == 'n')
					break;
			}
			break;
		}
		case 3: {
			viewMyBorrowerRecords();
			break;
		}
		case 4: {
			viewMyLenderRecords();
			break;
		}
		case 5: {
			viewMyBooks();
			break;
		}
		case 6: {
			viewAllUsers();
			break;
		}
		case 7: {
			on = false;
			//未设置currentUser = NULL 在调用BookSystemService的析构函数时会出现以下错误:
			//*** Error in `./main': free(): invalid pointer: 0x0000000001148028 ***
			//Aborted (core dumped)
			//此处有问题,因为currentUser初始化为NULL,且通过userLoGIn获得值,它不是通过new分配的,所以
			//在调用delete时出错,可如下处理:
			//currentUser = NULL;
			//其实在析构函数中根本不需要判断currentUser不为NULL时,调用delete,因为
			//currentUser不是动态new的,而是userLogin的返回值,所以这里是在析构函数中去掉

			break;
		}
		case 8: {
			while (true) {
				addBook();
				std::cout << " 继续添加书籍(y/n): ";
				char ys;
				std::cin >> ys;
				if (ys == 'n')
					break;
			}
			break;
		}
		case 9: {
			addMyAccountMoney();
			break;
		}
		case 10: {
			while (true) {
				deleteMybook();
				std::cout << " 继续删除书籍?(y/n): ";
				char ys;
				std::cin >> ys;
				if (ys == 'n')
					break;
			}
			break;
		}
		case 11: {
			while (true) {
				deleteMyRecord();
				std::cout << " 继续删除记录(y/n): ";
				char ys;
				std::cin >> ys;
				if (ys == 'n')
					break;
			}
			break;
		}
		case 12: {
			viewMyAccount();
			break;
		}
		case 13: {
			modifyMyAccount();
			break;
		}
		case 14: {
			on = deleteMyAccount();
			break;
		}
		case 15: {
			Client client;
			if (client.loginServer(currentUser->getName())) {
				client.Online();
			}
			break;
		}
	  }
	}
}
