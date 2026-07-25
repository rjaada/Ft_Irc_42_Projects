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

#include "Replies.hpp"

std::string err_norecipient(std::string target, std::string command)
{
	return ":ircserv 411 " + target + " :No recipient given (" + command + ")\r\n";
}

std::string err_notexttosend(std::string target)
{
	return ":ircserv 412 " + target + " :No text to send\r\n";
}