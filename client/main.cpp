#include<iostream>
#include"TcpClient.h"
#include"users_database.h"
#include<memory>
#include<windows.h>



int main()
{	
	//const std::string& addr, const std::string& user, const std::string& passwd, const std::string& database, unsigned int port
	std::shared_ptr<UsersDatabase> db = std::make_shared<UsersDatabase>("127.0.0.1", "root", "Wyz20050817.", "users", 3306);

	if (db->is_connected()) std::cout << "数据库连接成功" << std::endl;

	/*int choice;
	std::cout << "1.注册 2.登录" << std::endl;
	std::cin >> choice;
	std::string username, password;
	switch (choice)
	{
	case 1:
		
		std::cout << "请输入用户名:" << std::endl;
		std::cin >> username;
		std::cout << "请输入密码:" << std::endl;
		std::cin >> password;

		if (db->register_user(username, password))
		{
			std::cout << "注册成功" << std::endl;
		}
		else
		{
			std::cout << db->error_mes() << std::endl;
		}

		break;
	case 2:
		std::cout << "请输入用户名:" << std::endl;
		std::cin >> username;
		std::cout << "请输入密码:" << std::endl;
		std::cin >> password;
		if (db->login_user(username, password))
		{	
			std::cout << "登录成功!" << std::endl;
			std::cout << "-------------------------" << std::endl;
			std::cout << "欢迎用户 " << username << " !" << std::endl;
			while (true)
			{
				Sleep(1);
			}
		}
		else
		{
			std::cout << db->error_mes() << std::endl;
		}
		break;

	default:
		break;
	}*/

	for (int i = 0; i < 100; i++)
	{
		std::string username = "testuser" + std::to_string(i);
		std::string password = "testpass" + std::to_string(i);

		if (db->register_user(username, password))
		{
			std::cout << "注册用户 " << username << " 成功" << std::endl;
		}
		else
		{
			std::cout << "注册用户 " << username  << db->error_mes() << std::endl;
		}
	}



	return 0;
}