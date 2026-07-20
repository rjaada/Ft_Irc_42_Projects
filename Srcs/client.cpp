/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-20 14:11:28 by rjaada            #+#    #+#             */
/*   Updated: 2026-07-20 14:11:28 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void)
{
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	sockaddr_in serverAdress;
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_port = htons(8080);
	serverAdress.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAdress, sizeof(serverAdress));

	const char* message = "hello, server!";
	send(clientSocket, message, strlen(message), 0);

	close(clientSocket);

	return 0;
}