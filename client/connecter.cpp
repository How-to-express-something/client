#include "connecter.h"

Connecter::Connecter()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sock == INVALID_SOCKET)
	{
		WSACleanup();
		std::cerr << "Socket creation failed!" << std::endl;
	}
}



Connecter::~Connecter()
{
	close_connecter();
}

void Connecter::close_connect_to_server()
{
	closesocket(client_sock);
	client_sock = INVALID_SOCKET;
}

void Connecter::close_connecter()
{	
	closesocket(client_sock);
	WSACleanup();
}

int Connecter::connect_to_server(const char* ip, int port)
{	
	server_sock_addr.sin_family = AF_INET;
	server_sock_addr.sin_port = htons(port);
	/*server_sock_addr.sin_addr.S_un.S_addr = inet_addr(ip);*/
	inet_pton(AF_INET, ip, &server_sock_addr.sin_addr);

	if (client_sock == INVALID_SOCKET)
	{
		client_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (client_sock == INVALID_SOCKET)
		{
			WSACleanup();
			std::cerr << "Socket creation failed!" << std::endl;
		}
	}


	connect_fd = connect(client_sock, (sockaddr*)&server_sock_addr, sizeof(server_sock_addr));
	if (connect_fd == SOCKET_ERROR)
	{
		std::cerr << "Connection to server failed!" << std::endl;
		//TODO:³¢ÊÔÖØÁ¬
		close_connect_to_server();
		return -1;
	}


	return connect_fd;
}
