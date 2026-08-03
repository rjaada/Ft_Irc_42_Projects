#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP
# include "Channel.hpp"

class joinCommand
{
	private:

		std::string	_commType;
		std::string	_rawStr;
	
	public:

		joinCommand(std::string type, std::string rawStr);
		joinCommand(const joinCommand &other);
		joinCommand &operator=(const joinCommand &other);
		~joinCommand();

		std::string			getRawStr();
		std::string			getCommType();

};

void	newChannel(std::vector<Channel> &vec, std::string userName, std::string channelName);
void	joinCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string key);

#endif