#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <csignal>
#include "../../include/Client/Client.h"

std::mutex mtx;
std::condition_variable cv;
bool ready = false;
std::shared_ptr<Client> global_client;

void signalHandler(int signum)
{
	if (signum == SIGINT)
	{
		if (global_client)
		{
			global_client->sendToServer("disconnect");
			std::cout << "\nDisconnected 'cause 'Ctrl+C' signal.\n";
		}
		std::cout << std::endl;
		exit(signum);
	}
}

void receiveFromServer(Client &client)
{
	while (true)
	{
		std::string message = client.receiveFromServer();
		{
			std::lock_guard<std::mutex> lock(mtx);
			ready = true;
			std::cout << "Server has sent: " << message << std::endl;
		}
		cv.notify_one();
	}
}

void show_usage(std::string name)
{

	std::cerr << "Usage: " << name << " SERVER_IP PORT\n";
	std::cerr << "SERVER_IP can be 'this' to use the local IP address (127.0.0.1).\n";
	std::cerr << "Please provide the server's IPv4 address.\n";
}

int main(int argc, char *argv[])
{
	std::string server_ip;
	int port;

	if (argc < 3)
	{
		show_usage(argv[0]);
		return 1;
	}
	server_ip = argv[1] == std::string("this") ? "127.0.0.1" : argv[1];
	port = std::stoi(argv[2]);

	try
	{
		Client client(server_ip, port);
		global_client = std::make_shared<Client>(client);
		signal(SIGINT, signalHandler);
		std::thread receive_msg_thread(receiveFromServer, std::ref(client));

		std::string buffer;
		while (true)
		{
			std::cout << "Message: ";
			std::getline(std::cin, buffer);
			if (buffer == "disconnect")
			{
				client.sendToServer(buffer);
				break;
			}

			client.sendToServer(buffer);
			{
				std::unique_lock<std::mutex> lock(mtx);
				cv.wait(lock, []()
					   { return ready; });
			}
			ready = false;
		}

		std::cout << "\nDisconnected from a server . . .\n";

		receive_msg_thread.detach();
	}
	catch (const Client::ClientError &e)
	{
		std::cerr << "An error occurred: " << e.what() << '\n';
	}

	return 0;
}
