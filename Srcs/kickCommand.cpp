#include "kickCommand.hpp"

kickCommand::kickCommand(std::string type, std::string rawStr) : _commType(type),  _rawStr(rawStr)
{}

kickCommand::kickCommand(const kickCommand &other) : _commType(other._commType), _rawStr(other._rawStr)
{}

kickCommand &kickCommand::operator=(const kickCommand &other)
{
	if (this != &other)
	{
		this->_rawStr = other._rawStr;
		this->_commType = other._commType;
	}
	return (*this);
}

kickCommand::~kickCommand()
{}

std::string kickCommand::getRawStr()
{
	return (_rawStr);
}

std::string kickCommand::getCommType()
{
	return (_commType);
}
//username is the one being kicked, oper is the one kicking
void    operKickUser(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string oper, client &c, server &serv)
{
	if(findInServChanList(vec, channelName))
	{
		int i = getFromServChanListPos(vec, channelName);
		if (i == -1)
			return ;
		if (findInChanUserList(vec[i].getOps(), oper))
		{
			if (findInChanUserList(vec[i].getUsers(), userName))
			{
				vec[i].kickFromChannel(userName);
				std::cout << HCYN << "Operator: " HBLU "[" HCYN  << oper << HBLU "]" HCYN  " kicked "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " from "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;
				serv.sendToClient(c.get_fd(), ":You have kicked ");
				serv.sendToClient(c.get_fd(), userName);
				serv.sendToClient(c.get_fd(), " from ");
				serv.sendToClient(c.get_fd(), channelName);
				serv.sendToClient(c.get_fd(), "!\n");
				int	kUserFd = serv.findFdByNickname(userName);
				serv.sendToClient(kUserFd, ":You have been kicked from ");
				serv.sendToClient(kUserFd, channelName);
				serv.sendToClient(kUserFd, " by ");
				serv.sendToClient(kUserFd, oper);
				serv.sendToClient(kUserFd, "!\n");
				vec[i].printStatus();
				return ;
			}
			else
				std::cout << HCYN << "User: "  HBLU "[" HCYN << userName <<  HBLU "]" HCYN " not in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;
		}
		else
			std::cout << HCYN << "User: "  HBLU "[" HCYN << oper << HBLU "]" HCYN  " not operator of "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;
	}
}

void        kickCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string oper, client &c, server &serv)
{
	std::cout << HCYN << "----------------- In kickCommandExec ------------------" << std::endl;
	if(findInServChanList(vec, channelName))
	{
		operKickUser(vec, userName, channelName, oper, c, serv);
	}
	else
		std::cout << HCYN << "Channel: "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " doesn't exist!" << std::endl;
}

