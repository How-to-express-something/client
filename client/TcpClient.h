#pragma once
#include"connecter.h"

//��ɵ��ڶ������������������

class TcpClient
{
public:
	TcpClient(Connecter* connecter,const char* first_server_ip_,int first_server_port_)
		:connecter(connecter),first_server_ip(first_server_ip_),first_server_port(first_server_port_){};
	int run();
private:
	Connecter* connecter = nullptr;
	
	const char* first_server_ip;
	int first_server_port;

	const char* second_server_ip;
	int second_server_port;

	int first_server_fd;
	int second_server_fd;

};

