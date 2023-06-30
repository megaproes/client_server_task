#pragma once

#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <mutex>
#include <string>
#include <stdexcept>

class Client
{
public:
	class ClientError : public std::runtime_error
	{
	public:
		explicit ClientError(const std::string &msg) : std::runtime_error(msg) {}
	};

	Client(const std::string &server_ip, int port);
	~Client();
	void sendToServer(const std::string &message);
	std::string receiveFromServer();

private:
	std::string m_server_ip;
	int m_port;
	int m_client_socket;
};