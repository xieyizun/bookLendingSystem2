#include <iostream>
#include "User.cpp"
#include "Book.cpp"
#include "Record.cpp"
#include "BookManager.cpp"
#include "UserManager.cpp"
#include "RecordManager.cpp"
#include "SessionController.cpp"
#include "BookSystemService.cpp"

int main() {
	BookSystemService *service = new BookSystemService();

	bool on = true;

	bool connect = false; //避免在登陆失败或注册失败时,重新进行数据库连接

	while (on) {
		int select = service->welcome();

		if (select == 3) {
			on = false;
			continue;//直接退出
		} else if (select != 1 && select != 2) {
			std::cout << std::endl;
			std::cout << "\n 错误输入: 请输入1选择登陆,或者2选择注册, 或者3选择退出" << std::endl;
			continue;
		}

		//选择了1或2才进行数据库连接
		if (connect == false) {
			service->startService(); //启动系统,从数据库中读取数据
			//登陆或注册失败,重新登陆或注册时,防止先断开数据库,再重新连接数据库
			connect = true;
		}

		if (select == 1) {
			if (service->logInAccount()) {
				service->accountOnLine();
				//accountOnLine()中用户选择退出系统时,关闭与数据库的连接
				service->stopService();
				connect = false; //保证再次登陆时,重新进行数据库连接
			} else {
				std::cout << "\n 登陆失败!" << std::endl;
			}
		} else if (select == 2) {
			if (service->registerAccount()) {
				service->accountOnLine();
				//accountOnLine()中用户选择退出系统时,关闭与数据库的连接
				service->stopService();
				connect = false;//保证再次登陆时,重新进行数据库连接
			} else {
				std::cout << "\n 注册失败!" << std::endl;
			}
		}
	}
	if (service != NULL)
		delete service;

	return 0;
}