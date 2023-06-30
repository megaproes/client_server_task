#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

#include "../../include/Server/Server.h"

void printHelp()
{
	std::cout << "Usage: server_start [OPTIONS]\n";
	std::cout << "Options:\n";
	std::cout << "  --help    Display this help message\n";
	std::cout << "  --port    Set the server port (default: 5050)\n";
	std::cout << std::endl;
}

int main(int argc, char *argv[])
{
	try
	{
		int port = 5050; // Default port

		if (argc > 1)
		{
			std::string arg = argv[1];
			if (arg == "--help")
			{
				printHelp();
				return 0;
			}
			else if (arg == "--port" && argc > 2)
			{
				port = std::atoi(argv[2]);
			}
		}

		Server server(port);
		std::cout << "Server started on port: " << port << std::endl;
		std::cout << "Waiting for clients . . ." << std::endl;

		while (true)
		{
			server.acceptConnections();
		}
		std::cout << "Server closed . . .\n";
	}
	catch (const Server::ServerError &e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
