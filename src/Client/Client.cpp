#include "../../include/Client/Client.h"

Client::Client(const std::string &server_ip, int port) : m_server_ip(server_ip), m_port(port)
{
	m_client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_client_socket < 0)
	{
		throw ClientError("Socket creating failed: " + std::string(strerror(errno)));
	}

	sockaddr_in server_address{};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(m_port);
	if (inet_pton(AF_INET, m_server_ip.data(), &server_address.sin_addr) <= 0)
	{
		throw ClientError("Failed to convert server IP: " + std::string(strerror(errno)));
	}

	if (connect(m_client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		throw ClientError("Failed to connect to server: " + std::string(strerror(errno)));
	}
}

Client::~Client()
{
	close(m_client_socket);
}

void Client::sendToServer(const std::string &message)
{
	size_t total_bytes_sent = 0;
	size_t buf_size = strlen(message.data());

	while (total_bytes_sent < buf_size)
	{
		ssize_t bytes_sent = send(m_client_socket, message.data() + total_bytes_sent, buf_size - total_bytes_sent + 1, 0);
		if (bytes_sent == -1)
		{
			throw ClientError("Failed to send message: " + std::string(strerror(errno)));
		}
		total_bytes_sent += bytes_sent;
	}
}

std::string Client::receiveFromServer()
{
	char buffer[1024] = {};
	int result = recv(m_client_socket, buffer, sizeof(buffer), 0);
	if (result < 0)
	{
		throw ClientError("Failed to receive data: " + std::string(strerror(errno)));
	}
	else if (result == 0)
	{
		throw ClientError("Connection closed by server.");
	}
	else
	{
		return std::string(buffer);
	}
}
