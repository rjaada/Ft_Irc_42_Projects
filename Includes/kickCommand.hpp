#ifndef KICKCOMMAND_HPP
# define KICKCOMMAND_HPP
# include "Channel.hpp"
# include "Server.hpp"
# include "Client.hpp"

class kickCommand
{
	private:

		std::string	_commType;
		std::string	_rawStr;
	
	public:

		kickCommand(std::string type, std::string rawStr);
		kickCommand(const kickCommand &other);
		kickCommand &operator=(const kickCommand &other);
		~kickCommand();

		std::string			getRawStr();
		std::string			getCommType();

};

void	operKickUser(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string oper, client &c, server &serv);
void	kickCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string oper, client &c, server &serv);

#endif