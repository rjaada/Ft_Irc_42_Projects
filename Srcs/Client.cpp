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

#include "client.hpp"

client::client(int fd) : fd(fd), buffer(""), nickname(""), username(""), authenticated(false), registered(false){}

client::client(client const &other)
{
	*this = other;
}

client& client::operator=(client const &other)
{
	if(this != &other)
	{
		this->fd = other.fd;
		this->buffer = other.buffer;
		this->outBuffer = other.outBuffer;
		this->nickname = other.nickname;
		this->username = other.username;
		this->authenticated = other.authenticated;
		this->registered = other.registered;
	}
	return *this;
}

client::~client(){}

int client::get_fd()
{
	return this->fd;
}

std::string client::get_buffer()
{
	return this->buffer;
}

std::string client::get_outBuffer()
{
	return this->outBuffer;
}

std::string client::get_nickname()
{
	return this->nickname;
}

std::string client::get_username()
{
	return this->username;
}

bool client::is_authenticated()
{
	return this->authenticated;
}

bool client::is_registered()
{
	return this->registered;
}

void client::set_nickname(std::string nickname)
{
	this->nickname = nickname;
}

void client::set_username(std::string username)
{
	this->username = username;
}

void client::set_buffer(std::string buffer)
{
	this->buffer = buffer;
}

void client::set_outBuffer(std::string outBuffer)
{
	this->outBuffer = outBuffer;
}

void client::set_auth(bool authenticated)
{
	this->authenticated = authenticated;
}

void client::set_reg(bool registered)
{
	this->registered = registered;
}
