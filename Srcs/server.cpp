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

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

int	main(void)
{
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAdress;
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_port = htons(8080);
	serverAdress.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(serverSocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress));

	listen(serverSocket, 5);

	pollfd fds[100];
	fds[0].fd = serverSocket;
	fds[0].events = POLLIN;
	int nfds = 1;

	while (1)
	{
		poll(fds, nfds, -1);

		for (int i = 0; i < nfds; i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == serverSocket)
				{
					int newClient = accept(serverSocket, NULL, NULL);
					fds[nfds].fd = newClient;
					fds[nfds].events = POLLIN;
					nfds++;
				}
				else
				{
					char buffer[1024] = {0};
					int bytes = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (bytes <= 0)
					{
						close(fds[i].fd);
					}
					else
					{
						std::cout << "Message from client: " << buffer << std::endl;
					}
				}
			}
		}
	}

	close(serverSocket);

	return (0);
}