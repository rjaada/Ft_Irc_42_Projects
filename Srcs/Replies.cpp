/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-25 14:47:37 by rjaada            #+#    #+#             */
/*   Updated: 2026-07-25 14:47:37 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Replies.hpp"

//PRIVMSG
std::string err_norecipient(std::string target, std::string command)
{
	return ":ircserv 411 " + target + " :No recipient given (" + command + ")\r\n";
}

std::string err_notexttosend(std::string target)
{
	return ":ircserv 412 " + target + " :No text to send\r\n";
}

std::string err_nosuchnick(std::string target)
{
	return ":ircserv 401 " + target + " :No such nick/channel\r\n";
}

//REGISTRATION
std::string err_passwdmismatch()
{
	return ":ircserv 464 :Password incorrect !\r\n";
}

std::string err_nicknameinuse(std::string target)
{
	return ":ircserv 433 " + target + " :Nickname is already in use\r\n";
}

std::string err_nonicknamegiven(std::string target)
{
	return ":ircserv 431 " + target + " :No nickname given\r\n";
}

std::string err_erroneusnickname(std::string target)
{
	return ":ircserv 432 " + target + " :Erroneus nickname\r\n";
}

std::string err_needmoreparams(std::string target)
{
	return ":ircserv 461 " + target + " :Not enough parameters.\r\n";
}

std::string err_alreadyregistred(std::string target)
{
	return ":ircserv 462 " + target + " :You may not reregister!\r\n";
}
