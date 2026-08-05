#ifndef PARTCOMMAND_HPP
# define PARTCOMMAND_HPP
# include "Channel.hpp"
# include "Server.hpp"
# include "Client.hpp"

class partCommand
{
	private:

		std::string	_commType;
		std::string	_rawStr;
	
	public:

		partCommand(std::string type, std::string rawStr);
		partCommand(const partCommand &other);
		partCommand &operator=(const partCommand &other);
		~partCommand();

		std::string			getRawStr();
		std::string			getCommType();

};

void	leaveChannel(std::vector<Channel> &vec, std::string userName, std::string channelName, client &c, server &serv);
void	partCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, client &c, server &serv);

#endif