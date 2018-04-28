#pragma once

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "types.hpp"

#define BUFFER_LENGTH 1000

using namespace std; 

class Proxy
{
public:
	Proxy(int port_);
	~Proxy();

private:
	SOCKET sock; 
	struct sockaddr_in server, si_other;
	int port, slen, recv_len, packet_count;
	byte buf[BUFFER_LENGTH];
	WSADATA wsa; 

};

