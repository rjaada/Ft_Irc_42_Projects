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

// PRIVMSG
std::string err_norecipient(std::string target, std::string command)
{
	return (":ircserv 411 " + target + " :No recipient given (" + command
		+ ")\r\n");
}

std::string err_notexttosend(std::string target)
{
	return (":ircserv 412 " + target + " :No text to send\r\n");
}

std::string err_nosuchnick(std::string target)
{
	return (":ircserv 401 " + target + " :No such nick/channel\r\n");
}

std::string err_cannotsendtochan(std::string target)
{
	return (":ircserv 404 " + target + " :Cannot send to channel\r\n");
}

// JOIN
std::string err_inviteonlychan(std::string channel)
{
	return (":ircserv 473 " + channel + " :Cannot join channel (+i)\r\n");
}

std::string err_badchannelkey(std::string channel)
{
	return (":ircserv 475 " + channel + " :Cannot join channel (+k)\r\n");
}

std::string rpl_notopic(std::string nick, std::string channel)
{
	return (":ircserv 331 " + nick + " " + channel + " :No topic is set\r\n");
}

std::string rpl_topic(std::string nick, std::string channel,
	std::string topic)
{
	return (":ircserv 332 " + nick + " " + channel + " :" + topic + "\r\n");
}

std::string rpl_namreply(std::string nick, std::string channel,
	std::string names)
{
	return (":ircserv 353 " + nick + " = " + channel + " :" + names
		+ "\r\n");
}

std::string rpl_endofnames(std::string nick, std::string channel)
{
	return (":ircserv 366 " + nick + " " + channel
		+ " :End of /NAMES list\r\n");
}

// REGISTRATION
std::string rpl_welcome(std::string target)
{
	return (":ircserv 001 " + target + " :Welcome to the IRC server!\r\n");
}

std::string err_passwdmismatch()
{
	return (":ircserv 464 :Password incorrect !\r\n");
}

std::string err_nicknameinuse(std::string target)
{
	return (":ircserv 433 " + target + " :Nickname is already in use\r\n");
}

std::string err_nonicknamegiven(std::string target)
{
	return (":ircserv 431 " + target + " :No nickname given\r\n");
}

std::string err_erroneusnickname(std::string target)
{
	return (":ircserv 432 " + target + " :Erroneus nickname\r\n");
}

std::string err_needmoreparams(std::string target)
{
	return (":ircserv 461 " + target + " :Not enough parameters.\r\n");
}

std::string err_alreadyregistred(std::string target)
{
	return (":ircserv 462 " + target + " :You may not reregister!\r\n");
}

std::string err_cmdnotfound(std::string target, std::string command)
{
	return (":ircserv 421 " + target + " " + command + " :Unknown command\r\n");
}
