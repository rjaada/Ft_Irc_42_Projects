#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP
# include "Channel.hpp"
# include "../Includes/Colors.hpp"
# include "../Includes/Client.hpp"
# include "../Includes/Parser.hpp"
# include "../Includes/Replies.hpp"
# include "../Includes/Server.hpp"

class modeCommand
{
	private:

		std::string	_commType;
		std::string	_rawStr;
	
	public:

		modeCommand(std::string type, std::string rawStr);
		modeCommand(const modeCommand &other);
		modeCommand &operator=(const modeCommand &other);
		~modeCommand();

		std::string			getRawStr();
		std::string			getCommType();

};

void	modeCommandExec(std::vector<Channel> &vec, std::string cUser, std::string channelName, std::string mode, std::string param, client &c, server &serv);

#endif