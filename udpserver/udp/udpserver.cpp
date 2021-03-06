#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <iomanip>
#include <vector>

#include "types.hpp"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 8000  //Max length of buffer
#define PORT 2302   //The port on which to listen for incoming data

using namespace std;

void dump(byte * buffer, size_t size)
{
	cout << std::setfill('0');

	for (size_t offset = 0; offset < size; offset++)
	{
		if (offset % 10 == 0)
		{
			if (offset > 0) cout << '\n';

			cout << std::dec << std::setw(6) << offset << ": ";
			cout << std::hex << std::setw(2);
		}

		if (offset % 5 == 0) cout << "  ";

		cout << "0x" << (unsigned)*buffer++ << ' ';
	}
}

int receiveMessage()
{
	//Needs SOCKET, buf (buffer of char*), struct sockaddr_in  si_other, slen.
	int recieve_length;
	recieve_length = recvfrom(s, (char *)buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
	if (recieve_length == SOCKET_ERROR)
	{
		cout << "Error recieving message. Last error is: " << WSAGetLastError() << endl;
		exit(EXIT_FAILURE);
	}
	else
		return recieve_length;
}

int sendMessage(byte buffer_to_send[BUFLEN])
{
	int send_result;
	send_result = sendto(s, (char*)buffer_to_send, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
	if (send_result == SOCKET_ERROR)
	{
		cout << "Error sending message. Error code: " << WSAGetLastError() << endl;
		exit(EXIT_FAILURE);
	}
	else
		return send_result;
}

//Constructor to init all that the program needs to send/recieve messages.
void someConstrutor()
{
	//SOCKET s in class declaration.
	//struct sockaddr_in server, si_other. Way of accessing to the socket info. 
	//byte buffer [BUFLEN]. Declare the buffer of bytes (remember it's a typdef of uint8_t. Type definition at types.hpp)
	//WSADATA wsa needed to manage WSA details and info. 
	//slen to know about the size of 
}

int main()
{
	SOCKET s;
	bool running = false; 
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	byte buf[BUFLEN];
	WSADATA wsa;

	slen = sizeof(si_other);

	//Initialise winsock
	cout << "\nInitialising Winsock..." << endl;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "Failed. Error Code : " << WSAGetLastError();
		exit(EXIT_FAILURE);
	}

	cout << "Initialised." << endl;

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		cout << "Could not create socket. Error code: " << WSAGetLastError() << endl; 
	}
	cout << "Socket created." << endl;

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		cout << "Bind failed with error code : " << WSAGetLastError() << endl;
		exit(EXIT_FAILURE);
	}
	puts("Bind done");
	std::cout << "Listening in port " << PORT << "." << std::endl; 
	int packetcount = 0;
	running = true; 

	//keep listening for data
	while (running)
	{
		if (packetcount == 10)
			running = false;
		cout << "Waiting for data..." << endl; 
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		/*if ((recv_len = recvfrom(s, (char *)buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			cout << "recvfrom() failed with error code: " <<  WSAGetLastError() << endl;
			exit(EXIT_FAILURE);
		}*/
		cout << "" << endl; 
		cout << "" << endl;
		cout << "Received packet from: " << inet_ntoa(si_other.sin_addr) << " " << ntohs(si_other.sin_port) << endl;
		dump(buf, recv_len);
		packetcount++;
		//print details of the client/peer and the data received
		//printf("Data: %s\n", buf);

	}

	closesocket(s);
	WSACleanup();

	return 0;
}