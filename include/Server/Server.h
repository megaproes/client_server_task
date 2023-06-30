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

class Server
{
public:
	class ServerError : public std::runtime_error
	{
	public:
		explicit ServerError(const std::string &msg) : std::runtime_error(msg) {}
	};

	Server(int port);
	~Server();
	void acceptConnections();
	void handleClient(int client_socket);

private:
	int m_port;
	int m_server_socket;
	std::mutex m_count_mutex;
};