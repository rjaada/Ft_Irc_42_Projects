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

void server::processLine(client &c, std::string line)
{
	std::cout << "Client " << c.get_fd() << " sent line: [" << line << "]" << std::endl;
}

server::server()
{
}

server::server(int port, std::string password) : port(port), password(password)
{
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	fcntl(serverSocket, F_SETFL, O_NONBLOCK);
	
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
		this->clients = other.clients;
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
					this->clients.insert(std::make_pair(newClient, client(newClient)));
					fcntl(newClient, F_SETFL, O_NONBLOCK);
					this->fds[nfds].fd = newClient;
					this->fds[nfds].events = POLLIN;
					this->fds[nfds].revents = 0;
					this->nfds++;
				}
				else
				{
					char buffer[1024] = {0};
					int bytes = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (bytes <= 0)
					{
						close(this->fds[i].fd);
						this->clients.erase(this->fds[i].fd);
						this->fds[i] = this->fds[this->nfds - 1];
						this->nfds--;
						i--;
					}
					else
					{
						client &c = this->clients.find(fds[i].fd)->second;
						c.set_buffer(c.get_buffer() + buffer);

						std::string full = c.get_buffer();
						size_t pos;
						while ((pos = full.find("\r\n")) != std::string::npos)
						{
							std::string line = full.substr(0, pos);
							full.erase(0, pos + 2);
							processLine(c, line);
						}
						c.set_buffer(full);
					}
				}
			}
		}
	}
}