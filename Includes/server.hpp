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

# include <arpa/inet.h>
# include <cstring>
# include <iostream>
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <unistd.h>
# include <string>
# include <fcntl.h>

class server
{
	private:
		int serverSocket;
		int nfds;
		pollfd fds[100];
		sockaddr_in serverAdress;
		int port;
		std::string password;

	public:
		server();
		server(int port, std::string password);
		server(server const &other);
		server& operator=(server const &other);
		~server();

		void run();

};

#endif