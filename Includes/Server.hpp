/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 11:18:49 by rjaada            #+#    #+#             */
/*   Updated: 2026-07-21 11:18:49 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <arpa/inet.h>
# include <cstring>
# include <fcntl.h>
# include <iostream>
# include <map>
# include <netinet/in.h>
# include <poll.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>
# include <vector>

class server
{
  private:
	int serverSocket;
	int nfds;                      // how many fds actually used in fds[]
	pollfd fds[100];               // all fds we poll on, slot 0 always the listening socket
	std::map<int, client> clients; // fd -> client, quick lookup by fd
	sockaddr_in serverAdress;
	int port;
	std::string password;

  public:
	server();
	server(int port, std::string password);
	server(server const &other);
	server &operator=(server const &other);
	~server();

	void run();
	void processLine(client &c, std::string line
		/*, std::vector<Channel> &channels */);
	void sendToClient(int fd, std::string message);
	void disconnectClient(int index);
	void handleQuit(client &c);
	void handlePass(client &c, std::vector<std::string> params);
	void handleNick(client &c, std::vector<std::string> params);
	void handleUser(client &c, std::vector<std::string> params);
	void handlePrivmsg(client &c, std::vector<std::string> params);
	void tryCompleteRegistration(client &c);
};

#endif