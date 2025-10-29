#include "users_database.h"

UsersDatabase::~UsersDatabase()
{	
	//��̨��һ���������ʱ�� �ر�ʱ�������û�״̬��Ϊunactive
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
		error_message = "ע���û�ʧ��: " + std::string(mysql_error(&sql));
		mysql_close(&sql);
		return false;
	}

	if (!commit()) roll_back();

    return true;
}

bool UsersDatabase::login_user(const std::string& username, const std::string& password)
{
	//����û��Ƿ����
	start_transaction();

	snprintf(query, sizeof(query), "SELECT password,status FROM info WHERE username = '%s'", username.c_str());
	if (mysql_query(&sql, query))
	{
		error_message = "��ѯ�û�ʧ��: " + std::string(mysql_error(&sql));
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
		error_message = "�û�������";
		roll_back();
		return false;
	}

	//��������Ƿ���ȷ
	if (password != row[0])
	{
		error_message = "�������";
		roll_back();
		return false;
	}

	//����û�״̬�Ƿ�Ϊactive
	if (row[1] != nullptr && std::string(row[1]) == "active")
	{
		error_message = "�û����������豸��¼";
		roll_back();
		return false;
	}
	
	//���û�״̬��Ϊactive
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
		error_message = "�ع�����ʧ��: " + std::string(mysql_error(&sql));
		return false;
	}
	return true;
}

bool UsersDatabase::commit()
{
	if (mysql_query(&sql, "COMMIT")) {
		error_message = "�ύʧ��" + std::string(mysql_error(&sql));
		return false;
	}
	return true;
}
