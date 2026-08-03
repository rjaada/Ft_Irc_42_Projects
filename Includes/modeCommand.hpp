#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP
# include "Channel.hpp"

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

void	modeCommandExec(std::vector<Channel> &vec, std::string cUser, std::string channelName, std::string mode, std::string param);

#endif