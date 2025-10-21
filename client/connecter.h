#pragma once

//一次只能连接一个服务器

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<ws2tcpip.h>

#include<iostream>


class Connecter
{
public:
	Connecter();
	~Connecter();

	void close_connect_to_server();
	void close_connecter();
	int connect_to_server(const char* ip, int port);

private:
	SOCKET client_sock;
	sockaddr_in server_sock_addr;
	int connect_fd;

};

