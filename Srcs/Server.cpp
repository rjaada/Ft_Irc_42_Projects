/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 13:55:21 by rjaada            #+#    #+#             */
/*   Updated: 2026/08/01 16:36:04 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Client.hpp"
#include "../Includes/Parser.hpp"
#include "../Includes/Replies.hpp"
#include "../Includes/Server.hpp"
#include <sstream>

// rosa work on parsing here, dont touch
void server::processLine(client &c, std::string line)
{
	Parser input(line);
	input.parseStart();
	if (input.getIsCommConfirm() == 1)
	{
		std::string type = input.getCommType();
		std::vector<std::string> params = input.getParamVec();
		if (type == "PASS")
			handlePass(c, params);
		else if (type == "NICK")
			handleNick(c, params);
		else if (type == "USER")
			handleUser(c, params);
		else if (type == "PRIVMSG")
			handlePrivmsg(c, params);
		else if (type == "QUIT")
			handleQuit(c);
		/*else if(type == "JOIN")
			handleJoin();
		else if(type == "PART")
			handlePart();*/
	}
	else if (input.getIsCommConfirm() == -1
		|| input.getIsCommConfirm() == -2)
		sendToClient(c.get_fd(), err_needmoreparams(c.get_nickname()));
	else
		sendToClient(c.get_fd(), err_cmdnotfound(c.get_nickname(),
				line.substr(0, line.find(' '))));
}

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
			break ;
		}
	}
}

void server::handlePass(client &c, std::vector<std::string> params)
{
	if (params.size() < 2)
	{
		sendToClient(c.get_fd(), err_needmoreparams("*"));
		return ;
	}
	if (params[1] != this->password)
	{
		sendToClient(c.get_fd(), err_passwdmismatch());
		return ;
	}
	else
		c.set_auth(true);
}

void server::handleNick(client &c, std::vector<std::string> params)
{
	if (params.size() < 2)
	{
		sendToClient(c.get_fd(), err_nonicknamegiven("*"));
		return ;
	}
	for (std::map<int,
		client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.get_nickname() == params[1])
		{
			sendToClient(c.get_fd(), err_nicknameinuse("*"));
			return ;
		}
	}
	c.set_nickname(params[1]);
	tryCompleteRegistration(c);
}

void server::handleUser(client &c, std::vector<std::string> params)
{
	if (params.size() < 5)
	{
		sendToClient(c.get_fd(), err_needmoreparams("*"));
		return ;
	}
	if (c.is_registered())
	{
		sendToClient(c.get_fd(), err_alreadyregistred("*"));
		return ;
	}
	c.set_username(params[1]);
	tryCompleteRegistration(c);
}

// PASS + NICK + USER all done, but only fire the welcome once
void server::tryCompleteRegistration(client &c)
{
	if (c.is_registered())
		return ;
	if (c.is_authenticated() && !c.get_nickname().empty()
		&& !c.get_username().empty())
	{
		c.set_reg(true);
		sendToClient(c.get_fd(), rpl_welcome(c.get_nickname()));
	}
}

void server::handlePrivmsg(client &c, std::vector<std::string> params)
{
	client	*target;

	if (params.size() < 2)
	{
		sendToClient(c.get_fd(), err_norecipient("*", "PRIVMSG"));
		return ;
	}
	if (params.size() < 3)
	{
		sendToClient(c.get_fd(), err_norecipient("*", "PRIVMSG"));
		return ;
	}
	target = NULL;
	for (std::map<int,
		client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.get_nickname() == params[1])
		{
			target = &it->second;
			break ;
		}
	}
	if (!target)
	{
		sendToClient(c.get_fd(), err_nosuchnick(params[1]));
		return ;
	}
	sendToClient(target->get_fd(), ":" + c.get_nickname() + " PRIVMSG "
		+ params[1] + " :" + params[2] + "\r\n");
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
					int byteSent = send(fds[i].fd, check_buffer.c_str(),
							check_buffer.size(), 0);
					if (byteSent <= 0)
					{
						disconnectClient(i);
						continue ;
					}
					else
					{
						// send() can be partial, keep whatever didnt go out for next time
						check_buffer.erase(0, byteSent);
						b.set_outBuffer(check_buffer);
						// fully drained, stop watching for writable so poll() doesnt spam us
						if (check_buffer.empty())
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
						int clientFd = fds[i].fd;
						client &c = this->clients.find(clientFd)->second;
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
							// processLine may have run QUIT and erased this
							// client already (disconnectClient) -- c is a
							// dangling reference into freed memory now, stop
							if (this->clients.find(clientFd)
								== this->clients.end())
							{
								i--;
								break ;
							}
						}
						if (this->clients.find(clientFd) != this->clients.end())
							c.set_buffer(full);
					}
				}
			}
		}
	}
}