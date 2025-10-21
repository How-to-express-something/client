#include "TcpClient.h"

int TcpClient::run()
{	

	first_server_fd = connecter->connect_to_server(first_server_ip, first_server_port);

	return second_server_fd;
}
