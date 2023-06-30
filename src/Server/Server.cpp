#include "../../include/Server/Server.h"

Server::Server(int port) : m_port(port)
{
	m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_server_socket < 0)
		throw ServerError("Socket creation failed" + std::string(strerror(errno)));

	sockaddr_in server_address{};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(m_port);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int reuse = 1;
	if (setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
		throw ServerError("Failed to set SO_REUSEADDR option");

	if (bind(m_server_socket, reinterpret_cast<struct sockaddr *>(&server_address), sizeof(server_address)) < 0)
	{
		throw ServerError("Bind failed: " + std::string(strerror(errno)));
	}

	if (listen(m_server_socket, 1) < 0)
	{
		throw ServerError("Listen failed: " + std::string(strerror(errno)));
	}
}

Server::~Server()
{
	shutdown(m_server_socket, SHUT_RDWR);
}

void Server::acceptConnections()
{
	sockaddr_in client_address{};
	socklen_t client_len = sizeof(client_address);
	int client_socket = accept(m_server_socket, reinterpret_cast<struct sockaddr *>(&client_address), &client_len);
	if (client_socket < 0)
	{
		throw ServerError("Accept failed: " + std::string(strerror(errno)));
	}

	std::thread handleClient(&Server::handleClient, this, std::ref(client_socket));
	handleClient.detach();
}

void Server::handleClient(int client_socket)
{
	std::cout << "Client " << client_socket << " connected\n";

	char buffer[1024] = {};
	ssize_t bytes_read;
	while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0)
	{
		std::cout << "Received from " << client_socket << ": '" << buffer << "'\n";

		if (strcmp(buffer, "hello") == 0)
		{
			const char *world_buf = "world";
			send(client_socket, world_buf, sizeof(world_buf), 0);
			std::cout << "Send to " << client_socket << ": '" << world_buf << "'\n";
		}
		else if (strcmp(buffer, "disconnect") == 0)
		{
			shutdown(client_socket, SHUT_RDWR);
			std::cout << "Client " << client_socket << " has disconnected . . .\n";
			break;
		}
		else
		{
			send(client_socket, buffer, sizeof(buffer), 0);
			std::cout << "Send to " << client_socket << ": '" << buffer << "'\n";
		}
	}
}