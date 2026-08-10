/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:43:33 by rjaada            #+#    #+#             */
/*   Updated: 2026/08/10 16:04:27 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <iostream>
# include <string>

// PRIVMSG
std::string err_norecipient(std::string target, std::string command);
std::string err_notexttosend(std::string target);
std::string err_nosuchnick(std::string target);
std::string err_cannotsendtochan(std::string target);

// JOIN
std::string err_inviteonlychan(std::string channel);
std::string err_badchannelkey(std::string channel);
std::string err_bannedfromchan(std::string channel);
std::string err_channelisfull(std::string channel);
std::string rpl_notopic(std::string nick, std::string channel);
std::string rpl_topic(std::string nick, std::string channel,
	std::string topic);
std::string rpl_namreply(std::string nick, std::string channel,
	std::string names);
std::string rpl_endofnames(std::string nick, std::string channel);

// CHANNEL (PART/KICK/MODE/TOPIC/INVITE)
std::string err_chanoprivsneeded(std::string nick, std::string channel);
std::string err_notonchannel(std::string nick, std::string channel);
std::string err_nosuchchannel(std::string nick, std::string channel);
std::string err_useronchannel(std::string nick, std::string user,
	std::string channel);
std::string rpl_inviting(std::string nick, std::string target,
	std::string channel);

// REGISTRATION
std::string rpl_welcome(std::string target);
std::string err_passwdmismatch();
std::string err_nicknameinuse(std::string target);
std::string err_nonicknamegiven(std::string target);
std::string err_erroneusnickname(std::string target);
std::string err_needmoreparams(std::string target);
std::string err_alreadyregistred(std::string target);
std::string err_cmdnotfound(std::string target, std::string command);

#endif