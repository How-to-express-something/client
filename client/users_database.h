#pragma once

#include"database.h"
#include<cstring>
/*һ������ 
	�����û���Ϣ�����ݿ�
  ����ע��͵�¼ϵͳ

  ��һ����洢
* �û���¼�ɹ������Ϣ ǰ�˸�����Щ��Ⱦ
* ͷ�� ʹ�ü�¼ ��
* ��ι��������
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

