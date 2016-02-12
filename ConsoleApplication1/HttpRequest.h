#pragma once
#ifndef M_HTTP_REQUEST_
#define M_HTTP_REQUEST_
#include<WS2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
class HttpRequest {
public:
	HttpRequest();
	~HttpRequest();
	void printIP();
	void setUrl(PCSTR url);
	void setPort(PCSTR port);
	void addHeader(char *str);
	void addHeaderln(char *str);
	void setFamily(int fm);
	void setBuffer(int size);
	void setTservname(PCSTR serverName);
	void setIpPortocol(int ipProto);
	void setSocketType(int type);
	/*
		0 : success
		-1: socket error
		1 : url = null
		2 : Failed to set target Address.
		3 : Socket Failed!
		else 
			connect function errcode
	*/
	int scand();
	int scandAndSaveToTxt();
private:
	int bufferSize = 10000;
	HttpRequest & operator=(HttpRequest & tmp);
	PCSTR url = nullptr;
	PCSTR port = nullptr;
	char *buffer = nullptr;
	std::string header;
	addrinfo hint;
	addrinfo *targetAddressInfo;
	SOCKET webSocket;
	WSADATA wsaData;
};
#endif // !M_HTTP_REQUEST_