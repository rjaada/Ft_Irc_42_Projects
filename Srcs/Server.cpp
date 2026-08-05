/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 13:55:21 by rjaada            #+#    #+#             */
/*   Updated: 2026/08/05 17:05:45 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Channel.hpp"
#include "../Includes/Client.hpp"
#include "../Includes/Parser.hpp"
#include "../Includes/Replies.hpp"
#include "../Includes/Server.hpp"
#include "../Includes/joinCommand.hpp"
#include "../Includes/partCommand.hpp"
#include "../Includes/kickCommand.hpp"
#include "../Includes/inviteCommand.hpp"
#include "../Includes/topicCommand.hpp"
#include "../Includes/modeCommand.hpp"
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
		else if (type == "JOIN")
			handleJoin(c, params);
		else if (type == "PART")
			partCommandExec(this->channels, c.get_nickname(), params[1], c, *this);
		else if (type == "KICK")
			kickCommandExec(this->channels, params[2], params[1],
				c.get_nickname(), c, *this);
		else if (type == "INVITE")
			inviteCommandExec(this->channels, params[1], params[2],
				c.get_nickname(), c, *this);
		else if (type == "TOPIC")
			topicCommandExec(this->channels, c.get_nickname(), params[1],
				params.size() > 2 ? params[2] : "", params.size() - 1, c, *this);
		else if (type == "MODE")
			modeCommandExec(this->channels, c.get_nickname(), params[1],
				params[2], params.size() > 3 ? params[3] : "", c, *this);
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
		this->channels = other.channels;
		for (int i = 0; i < 100; i++)
			this->fds[i] = other.fds[i];
	}
	return (*this);
}

server::~server()
{
}

void server::removeClientFromChannels(std::string nickname)
{
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (!findInChanUserList(this->channels[i].getUsers(), nickname))
			continue ;
		std::vector<std::string> members = this->channels[i].getUsers();
		for (size_t m = 0; m < members.size(); m++)
		{
			if (members[m] == nickname)
				continue ;
			int memberFd = findFdByNickname(members[m]);
			if (memberFd != -1)
				sendToClient(memberFd, ":" + nickname
					+ " QUIT :Client quit\r\n");
		}
		this->channels[i].partFromChannel(nickname);
	}
}

void server::disconnectClient(int index)
{
	// send failed, connection is dead, drop the client
	int fd = this->fds[index].fd;
	std::map<int, client>::iterator it = this->clients.find(fd);
	if (it != this->clients.end())
		removeClientFromChannels(it->second.get_nickname());
	close(fd);
	this->clients.erase(fd);
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

// find the fd for a nickname, or -1 if nobody currently has it
int server::findFdByNickname(std::string nickname)
{
	for (std::map<int,
		client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.get_nickname() == nickname)
			return (it->first);
	}
	return (-1);
}

void server::handlePrivmsgChannel(client &c, std::string channelName,
	std::string text)
{
	if (!findInServChanList(this->channels, channelName))
	{
		sendToClient(c.get_fd(), err_nosuchnick(channelName));
		return ;
	}
	int i = getFromServChanListPos(this->channels, channelName);
	if (!findInChanUserList(this->channels[i].getUsers(), c.get_nickname()))
	{
		sendToClient(c.get_fd(), err_cannotsendtochan(channelName));
		return ;
	}
	std::vector<std::string> members = this->channels[i].getUsers();
	for (size_t m = 0; m < members.size(); m++)
	{
		if (members[m] == c.get_nickname())
			continue ;
		int fd = findFdByNickname(members[m]);
		if (fd != -1)
			sendToClient(fd, ":" + c.get_nickname() + " PRIVMSG "
				+ channelName + " " + text + "\r\n");
	}
}

void server::handleJoin(client &c, std::vector<std::string> params)
{
	std::string channelName = params[1];
	std::string key = params.size() > 2 ? params[2] : "";

	joinCommandExec(this->channels, c.get_nickname(), channelName, key, c, *this);

	if (!findInServChanList(this->channels, channelName))
		return ; // exec always creates the channel if it didn't exist
	int i = getFromServChanListPos(this->channels, channelName);
	if (!findInChanUserList(this->channels[i].getUsers(), c.get_nickname()))
	{
		// join was refused -- figure out which restriction blocked it
		if (this->channels[i].isModeI())
			sendToClient(c.get_fd(), err_inviteonlychan(channelName));
		else if (this->channels[i].isModeK()
			&& this->channels[i].getKey() != key)
			sendToClient(c.get_fd(), err_badchannelkey(channelName));
		return ;
	}

	std::vector<std::string> members = this->channels[i].getUsers();
	for (size_t m = 0; m < members.size(); m++)
	{
		int fd = findFdByNickname(members[m]);
		if (fd != -1)
			sendToClient(fd, ":" + c.get_nickname() + " JOIN " + channelName
				+ "\r\n");
	}

	std::string topic = this->channels[i].getTopic();
	if (topic.empty())
		sendToClient(c.get_fd(), rpl_notopic(c.get_nickname(), channelName));
	else
		sendToClient(c.get_fd(), rpl_topic(c.get_nickname(), channelName,
				topic));

	std::string names;
	for (size_t m = 0; m < members.size(); m++)
	{
		if (!names.empty())
			names += " ";
		names += members[m];
	}
	sendToClient(c.get_fd(), rpl_namreply(c.get_nickname(), channelName,
			names));
	sendToClient(c.get_fd(), rpl_endofnames(c.get_nickname(), channelName));
}

void server::handlePrivmsg(client &c, std::vector<std::string> params)
{
	if (params.size() < 2)
	{
		sendToClient(c.get_fd(), err_norecipient("*", "PRIVMSG"));
		return ;
	}
	if (params.size() < 3)
	{
		sendToClient(c.get_fd(), err_notexttosend("*"));
		return ;
	}
	if (params[1][0] == '#' || params[1][0] == '&')
	{
		handlePrivmsgChannel(c, params[1], params[2]);
		return ;
	}
	int fd = findFdByNickname(params[1]);
	if (fd == -1)
	{
		sendToClient(c.get_fd(), err_nosuchnick(params[1]));
		return ;
	}
	sendToClient(fd, ":" + c.get_nickname() + " PRIVMSG "
		+ params[1] + " " + params[2] + "\r\n");
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