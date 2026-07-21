#include <iostream>
//#include <string>
//#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <exception>
#include <csignal>

//#include <cctype>
#include <cstdlib>
#include "server.hpp"

static void		handleSignal(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
		std::cout << "Bye bye!" << std::endl;
	exit(0);
}

void	argChecker(char **av)
{
	std::string portStr = av[1];

	int	portNum = atoi(av[1]);

	if (portStr.find_first_not_of("0123456789") != std::string::npos)
		throw std::invalid_argument("Port should be a number, please!");

	if (portNum < 1024 || portNum > 65535)
		throw std::invalid_argument("Invalid port number! Please use a number between 1024 and 65535.");

	int i = 0;
	while(av[2][i])
	{
		if (!(isalnum(av[2][i])))
		{
			throw std::invalid_argument("Password should be alphanumeric, please!");
			return ;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Wrong arguments!"<< std::endl;
		std::cerr << "Should be: ./ircserv <port number> <password>"<< std::endl;
		return (1);
	}

	std::string port = av[1];
	std::string pass = av[2];

	try
	{
		signal(SIGINT, handleSignal);
		signal(SIGQUIT, handleSignal);
		std::cout << "\nPort number: " << port << "\nPassword: " << pass << "\n"<< std::endl;
		argChecker(av);
		std::cout << "All args are valid, server starts here." << std::endl;
		int portNum = atoi(av[1]);
		server irc(portNum, pass);
		irc.run();
	}
	catch (const std::exception &e)
	{
		//close fds here
		std::cerr << "ERROR: " << e.what() << std::endl;
		return (1);
	}
	//when the loop is stopped and the server is closed
	std::cout << "the server is closed!" << std::endl;
	return (0);
}