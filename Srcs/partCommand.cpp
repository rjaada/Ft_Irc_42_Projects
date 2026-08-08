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
			std::vector<std::string> members = vec[i].getUsers();
			std::string partMsg = ":" + userName + " PART " + channelName
				+ " :" + userName + "\r\n";
			for (size_t m = 0; m < members.size(); m++)
			{
				std::string memberNick = members[m];
				if (!memberNick.empty() && memberNick[0] == '@')
					memberNick = memberNick.substr(1);
				int fd = serv.findFdByNickname(memberNick);
				if (fd != -1)
					serv.sendToClient(fd, partMsg);
			}
			vec[i].partFromChannel(userName);
			std::cout << HCYN << "User: "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " left " HBLU "[" HCYN  << channelName << HBLU "]" HCYN  " channel!" <<std::endl;
			vec[i].printStatus();
			return ;
		}
		else
		{
			serv.sendToClient(c.get_fd(), err_notonchannel(userName, channelName));
			std::cout << HCYN << "User: "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " not in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;
		}

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
	{
		serv.sendToClient(c.get_fd(), err_nosuchchannel(userName, channelName));
		std::cout << HCYN << "Channel: " HBLU "[" HCYN  <<channelName << HBLU "]" HCYN  " doesn't exist!" << std::endl;
	}
}

