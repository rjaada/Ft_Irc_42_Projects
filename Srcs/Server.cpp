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

#include "../Includes/Client.hpp"
#include "../Includes/Server.hpp"
#include "../Includes/Replies.hpp"
#include <sstream>

// rosa work on parsing here, dont touch
void server::processLine(client &c, std::string line)
{
	std::cout << "Client " << c.get_fd() << " sent line: [" << line << "]" << std::endl;
	// TEMP TEST FOR PASS
	if (line.substr(0, 5) == "PASS ")
	{
		std::vector<std::string> params;
		params.push_back("PASS");
		params.push_back(line.substr(5));
		handlePass(c, params);
	}
	// TEMP TEST FOR NICK
	if(line.substr(0, 5) == "NICK ")
	{
		std::vector<std::string> params;
		params.push_back("NICK");
		params.push_back(line.substr(5));
		handleNick(c, params);
	}
	// TEMP TEST FOR USER
	if (line.substr(0, 5) == "USER ")
	{
		std::vector<std::string> params;
		std::istringstream iss(line);
		std::string token;
		while (iss >> token)
			params.push_back(token);
		handleUser(c, params);
	}
	// TEMP TEST FOR PRIVMSG
	if (line.substr(0, 8) == "PRIVMSG ")
	{
		std::string rest = line.substr(8);
		size_t colon = rest.find(':');
		std::string target = rest.substr(0, colon - 1);
		std::string msg = rest.substr(colon + 1);
		std::vector<std::string> params;
		params.push_back("PRIVMSG");
		params.push_back(target);
		params.push_back(msg);
		handlePrivmsg(c, params);
	}
}

// queue a message for a client, dont send it here, poll() will send it when ready
void server::sendToClient(int fd, std::string message)
{
	client &c = this->clients.find(fd)->second;
	c.set_outBuffer(c.get_outBuffer() + message);
	// find this fd slot in fds[] and arm POLLOUT so poll() watches for writable too
	for (int i = 0; i < nfds; i++)
	{
		if (fds[i].fd == fd)
		{
			fds[i].events = POLLIN | POLLOUT;
		}
	}
}

server::server()
{
}

server::server(int port, std::string password) : port(port), password(password)
{
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	// non blocking, subject says every fd must be non blocking
	fcntl(serverSocket, F_SETFL, O_NONBLOCK);
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_port = htons(this->port);
	serverAdress.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(serverSocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress));
	listen(serverSocket, 5);
	// listening socket goes in slot 0, watched for POLLIN (new connections)
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

void server::disconnectClient(int index)
{
	// send failed, connection is dead, drop the client
	close(this->fds[index].fd);
	this->clients.erase(this->fds[index].fd);
	// swap remove, last fd takes this slot so array stays packed
	this->fds[index] = this->fds[this->nfds - 1];
	this->nfds--;
	index--;
}

void server::handleQuit(client &c)
{
	for (int i = 0; i < nfds; i++)
	{
		if (fds[i].fd == c.get_fd())
		{
			disconnectClient(i);
			break;
		}
	}
}

void server::handlePass(client &c, std::vector<std::string> params)
{
	if(params.size() < 2)
	{
		sendToClient(c.get_fd(), err_needmoreparams("*"));
		return;
	}
	if(params[1] != this->password)
	{
		sendToClient(c.get_fd(), err_passwdmismatch());
		return;
	}
	else
		c.set_auth(true);
}

void server::handleNick(client &c, std::vector<std::string> params)
{
	if (params.size() < 2)
	{
		sendToClient(c.get_fd(), err_nonicknamegiven("*"));
		return;
	}
	for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.get_nickname() == params[1])
		{
			sendToClient(c.get_fd(), err_nicknameinuse("*"));
			return;
		}
	}
	c.set_nickname(params[1]);
}

void server::handleUser(client &c, std::vector<std::string> params)
{
	if(params.size() < 5)
	{
		sendToClient(c.get_fd(), err_needmoreparams("*"));
		return;
	}
	if(c.is_registered())
	{
		sendToClient(c.get_fd(), err_alreadyregistred("*"));
		return;
	}
	c.set_username(params[1]);
}

void server::handlePrivmsg(client &c, std::vector<std::string> params)
{
	if(params.size() < 2)
	{
		sendToClient(c.get_fd(), err_norecipient("*", "PRIVMSG"));
		return;
	}
	if(params.size() < 3)
	{
		sendToClient(c.get_fd(), err_norecipient("*", "PRIVMSG"));
		return;
	}
	client *target = NULL;
	
	for(std::map<int, client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if(it->second.get_nickname() == params[1])
		{
			target = &it->second;
			break;
		}
	}
	if(!target)
	{
		sendToClient(c.get_fd(), err_nosuchnick(params[1]));
		return;
	}
	sendToClient(target->get_fd(), ":" + c.get_nickname() + " PRIVMSG " + params[1] + " :" + params[2] + "\r\n");
}

void server::run()
{
	while (1)
	{
		// only poll() call in the whole prog, blocks till something is ready
		poll(this->fds, this->nfds, -1);

		for (int i = 0; i < this->nfds; i++)
		{
			// this fd is ready to receive bytes without blocking, try to flush outBuffer
			if (this->fds[i].revents & POLLOUT)
			{
				client &b = this->clients.find(fds[i].fd)->second;
				std::string check_buffer = b.get_outBuffer();

				// nothing queued for this client, dont bother calling send
				if (!check_buffer.empty())
				{
					int byteSent = send(fds[i].fd, check_buffer.c_str(), check_buffer.size(), 0);
					if (byteSent <= 0)
					{
						disconnectClient(i);
						continue;
					}
					else
					{
						// send() can be partial, keep whatever didnt go out for next time
						check_buffer.erase(0, byteSent);
						b.set_outBuffer(check_buffer);
						// fully drained, stop watching for writable so poll() doesnt spam us
						if(check_buffer.empty())
							this->fds[i].events = POLLIN;
					}
				}
			}

			if (this->fds[i].revents & POLLIN)
			{
				if (this->fds[i].fd == this->serverSocket)
				{
					// listening socket ready = new client waiting, accept it
					int newClient = accept(this->serverSocket, NULL, NULL);
					this->clients.insert(std::make_pair(newClient,
							client(newClient)));
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
						disconnectClient(i);
						i--;
					}
					else
					{
						client &c = this->clients.find(fds[i].fd)->second;
						c.set_buffer(c.get_buffer() + buffer);

						// recv can give partial lines or multiple lines at once
						// so we keep everything in the client buffer and only
						// pull out full lines, \r\n terminated, leftover stays
						std::string full = c.get_buffer();
						size_t pos;
						while ((pos = full.find("\r\n")) != std::string::npos)
						{
							std::string line = full.substr(0, pos);
							full.erase(0, pos + 2);
							processLine(c, line);
							// tempo, just to test the send pipeline, echoes back what u typed
							sendToClient(c.get_fd(), line + "\r\n");
						}
						c.set_buffer(full);
					}
				}
			}
		}
	}
}