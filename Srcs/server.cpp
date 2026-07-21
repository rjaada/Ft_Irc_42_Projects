/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-20 13:55:21 by rjaada            #+#    #+#             */
/*   Updated: 2026-07-20 13:55:21 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server()
{
}

server::server(int port, std::string password) : port(port), password(password)
{
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	serverAdress.sin_family = AF_INET;
	serverAdress.sin_port = htons(this->port);
	serverAdress.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(serverSocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress));

	listen(serverSocket, 5);

	fds[0].fd = serverSocket;
	fds[0].events = POLLIN;
	this->nfds = 1;
}

server::server(server const &other)
{
	*this = other;
}

server &server::operator=(server const &other)
{
	if (this != &other)
	{
		this->serverSocket = other.serverSocket;
		this->serverAdress = other.serverAdress;
		this->nfds = other.nfds;
		this->port = other.port;
		this->password = other.password;
		for (int i = 0; i < 100; i++)
			this->fds[i] = other.fds[i];
	}
	return (*this);
}

server::~server()
{
}

void server::run()
{
	while (1)
	{
		poll(this->fds, this->nfds, -1);

		for (int i = 0; i < this->nfds; i++)
		{
			if (this->fds[i].revents & POLLIN)
			{
				if (this->fds[i].fd == this->serverSocket)
				{
					int newClient = accept(this->serverSocket, NULL, NULL);
					this->fds[nfds].fd = newClient;
					this->fds[nfds].events = POLLIN;
					this->nfds++;
				}
				else
				{
					char buffer[1024] = {0};
					int bytes = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (bytes <= 0)
					{
						close(this->fds[i].fd);
					}
					else
					{
						std::cout << "Message from client: " << buffer << std::endl;
					}
				}
			}
		}
	}
}