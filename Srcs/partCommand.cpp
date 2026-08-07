#include "partCommand.hpp"

partCommand::partCommand(std::string type, std::string rawStr) : _commType(type),  _rawStr(rawStr)
{}

partCommand::partCommand(const partCommand &other) : _commType(other._commType), _rawStr(other._rawStr)
{}

partCommand &partCommand::operator=(const partCommand &other)
{
	if (this != &other)
	{
		this->_rawStr = other._rawStr;
		this->_commType = other._commType;
	}
	return (*this);
}

partCommand::~partCommand()
{}

std::string partCommand::getRawStr()
{
	return (_rawStr);
}

std::string partCommand::getCommType()
{
	return (_commType);
}

void    leaveChannel(std::vector<Channel> &vec, std::string userName, std::string channelName, client &c, server &serv)
{
	if(findInServChanList(vec, channelName))
	{
		int i = getFromServChanListPos(vec, channelName);
		if (i == -1)
			return ;
		if (findInChanUserList(vec[i].getUsers(), userName) || findInChanUserList(vec[i].getUsers(), '@' + userName))
		{
			vec[i].partFromChannel(userName);
			std::cout << HCYN << "User: "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " left " HBLU "[" HCYN  << channelName << HBLU "]" HCYN  " channel!" <<std::endl;
			serv.sendToClient(c.get_fd(), ":You just left channel ");
			serv.sendToClient(c.get_fd(), channelName);
			serv.sendToClient(c.get_fd(), ". Goodbye!\n");
			vec[i].printStatus();
			return ;
		}
		else
			std::cout << HCYN << "User: "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " not in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;

	}

}
//username is the one parting from channel
void        partCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, client &c, server &serv)
{
	std::cout << HCYN << "----------------- In partCommandExec --------------" << std::endl;
	if(findInServChanList(vec, channelName))
	{
		leaveChannel(vec, userName, channelName, c, serv);
	}
	else
		std::cout << HCYN << "Channel: " HBLU "[" HCYN  <<channelName << HBLU "]" HCYN  " doesn't exist!" << std::endl;
}

