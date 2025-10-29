#pragma once

#include"database.h"
#include<cstring>
/*一个表负责 
	所有用户信息的数据库
  负责注册和登录系统

  另一个表存储
* 用户登录成功后的信息 前端根据这些渲染
* 头像 使用记录 等
* 如何构建这个表？
*/


class UsersDatabase : public Database
{

public:
	UsersDatabase(const std::string& addr, const std::string& user, const std::string& passwd, const std::string& database, unsigned int port) : Database(addr, user, passwd, database, port) {
	};
	~UsersDatabase();

	bool register_user(const std::string& username, const std::string& password);
	bool login_user(const std::string& username, const std::string& password);

	void start_transaction() {mysql_query(&sql, "START TRANSACTION");}

	bool roll_back();
	bool commit();
};

