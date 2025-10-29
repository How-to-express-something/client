#include "users_database.h"

UsersDatabase::~UsersDatabase()
{	
	//单台第一类服务器的时候 关闭时将所有用户状态设为unactive
	start_transaction();
	/*mysql_query(&sql,"UPDATE info SET status = 'inactive'");*/
	if (!commit()) roll_back();

	if (!connected)
		mysql_close(&sql);
}

bool UsersDatabase::register_user(const std::string& username, const std::string& password)
{   
	start_transaction();
	snprintf(query, sizeof(query), "INSERT INTO info(username,password,entry_date,status) values('%s','%s',current_date(),'inactive')",username.c_str(), password.c_str());


	int unsuccess = mysql_query(&sql, query);
	if (unsuccess)
	{
		error_message = "注册用户失败: " + std::string(mysql_error(&sql));
		mysql_close(&sql);
		return false;
	}

	if (!commit()) roll_back();

    return true;
}

bool UsersDatabase::login_user(const std::string& username, const std::string& password)
{
	//检测用户是否存在
	start_transaction();

	snprintf(query, sizeof(query), "SELECT password,status FROM info WHERE username = '%s'", username.c_str());
	if (mysql_query(&sql, query))
	{
		error_message = "查询用户失败: " + std::string(mysql_error(&sql));
		roll_back();
		return false;
	}

	res = mysql_store_result(&sql);
	if (mysql_num_rows(res))
	{
		row = mysql_fetch_row(res);
	}
	else
	{
		error_message = "用户不存在";
		roll_back();
		return false;
	}

	//检测密码是否正确
	if (password != row[0])
	{
		error_message = "密码错误";
		roll_back();
		return false;
	}

	//检测用户状态是否为active
	if (row[1] != nullptr && std::string(row[1]) == "active")
	{
		error_message = "用户已在其他设备登录";
		roll_back();
		return false;
	}
	
	//将用户状态设为active
	snprintf(query, sizeof(query),"UPDATE info SET status = 'active' WHERE username = '%s'", username.c_str());
	mysql_query(&sql, query);
	if (!commit()) {
		roll_back(); return false;
	}

	mysql_free_result(res);
	return true;

}

bool UsersDatabase::roll_back()
{
	if (mysql_query(&sql, "ROLLBACK")) {
		error_message = "回滚事务失败: " + std::string(mysql_error(&sql));
		return false;
	}
	return true;
}

bool UsersDatabase::commit()
{
	if (mysql_query(&sql, "COMMIT")) {
		error_message = "提交失败" + std::string(mysql_error(&sql));
		return false;
	}
	return true;
}
