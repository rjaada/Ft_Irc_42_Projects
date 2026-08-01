/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-25 14:43:33 by rjaada            #+#    #+#             */
/*   Updated: 2026-07-25 14:43:33 by rjaada           ###   ########.fr       */
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