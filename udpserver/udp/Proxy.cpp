#include "stdafx.h"
#include "Proxy.hpp"


Proxy::Proxy(int port_) : port(port_)
{
	slen = sizeof(si_other);
	this->packet_count = 0; 

	//Initialise winsock
	cout << "\nInitialising Winsock..." << endl;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "Failed. Error Code : " << WSAGetLastError();
		exit(EXIT_FAILURE);
	}

	cout << "Initialised." << std::endl;

	//Create a socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		cout << "Could not create socket. Error code: " << WSAGetLastError() << endl;
	}
	cout << "Socket created." << endl;

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(this->port);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		cout << "Bind failed with error code : " << WSAGetLastError() << endl;
		exit(EXIT_FAILURE);
	}
	puts("Bind done");
	std::cout << "Listening in port " << this->port << "." << std::endl;
}


Proxy::~Proxy()
{
}
