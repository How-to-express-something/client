#pragma once

#include<mysql.h>
#include<string>
//用户的数据库操作类
#include<iostream>

/*	数据库基类
*	完成连接到各个数据库 用户信息数据库 用户各个记录
*/

//每个用户还有运算记录等 使用记录等

class Database
{
public:
	Database(const std::string& addr, const std::string& user,const std::string& passwd, const std::string& database, unsigned int port)
	{
		mysql_init(&sql);
		mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "gbk");
		if (mysql_real_connect(&sql, addr.c_str(), user.c_str(), passwd.c_str(), database.c_str(), port, NULL, 0) == NULL)
		{
			std::cerr << "数据库连接失败" << mysql_error(&sql) << std::endl;
			connected = false;
		}
		else
		{
			connected = true;
		}
	}

	/*Database(const char* addr, const char* user, const char* passwd, const char* database, unsigned int port)
	{
		mysql_init(&sql);
		mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "gbk");
		if (mysql_real_connect(&sql, addr, user, passwd, database, port, NULL, 0) == NULL)
		{
			std::cerr << "数据库连接失败" << mysql_error(&sql) << std::endl;
			connected = false;
		}
		else
		{
			connected = true;
		}
	}*/

	~Database()
	{
		if (!connected)
			mysql_close(&sql);
	}



	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	bool is_connected() const;
	
	std::string error_mes() const
	{
		return error_message;
	}

protected:
	MYSQL sql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	bool connected = false;
	std::string error_message;
	char query[256];
};

