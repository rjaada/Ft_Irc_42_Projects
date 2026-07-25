/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 15:21:28 by rjaada            #+#    #+#             */
/*   Updated: 2026-07-21 15:21:28 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <arpa/inet.h>
# include <cstring>
# include <iostream>
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <unistd.h>
# include <string>
# include <fcntl.h>

class client
{
	private:
		int fd;
		std::string buffer;
		std::string outBuffer; // stuff queued to send, waits here till poll says fd is writable
		std::string nickname;
		std::string username;
		bool authenticated; // pass checked ok
		bool registered; // nick + user both set

	public:
		client(int fd);
		client(client const &other);
		client& operator=(client const &other);
		~client();

		//getters
		int get_fd();
		std::string get_buffer();
		std::string get_outBuffer();
		std::string get_nickname();
		std::string get_username();
		bool is_authenticated();
		bool is_registered();

		//setters
		void set_nickname(std::string nickname);
    	void set_username(std::string username);
    	void set_buffer(std::string buffer);
		void set_outBuffer(std::string outBuffer);
		void set_auth(bool authenticated);
		void set_reg(bool registered);



};


#endif