#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP
# include "Channel.hpp"

class inviteCommand
{
	private:

		std::string	_commType;
		std::string	_rawStr;
	
	public:

		inviteCommand(std::string type, std::string rawStr);
		inviteCommand(const inviteCommand &other);
		inviteCommand &operator=(const inviteCommand &other);
		~inviteCommand();

		std::string			getRawStr();
		std::string			getCommType();

};

void	inviteCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string cUser);

#endif