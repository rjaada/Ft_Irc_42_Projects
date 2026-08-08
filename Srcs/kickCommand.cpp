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
		if (findInChanUserList(vec[i].getOps(), '@' + oper))
		{
			if (findInChanUserList(vec[i].getUsers(), userName) || findInChanUserList(vec[i].getUsers(), '@' + userName))
			{
				std::vector<std::string> members = vec[i].getUsers();
				std::string kickMsg = ":" + oper + " KICK " + channelName
					+ " " + userName + " :" + oper + "\r\n";
				for (size_t m = 0; m < members.size(); m++)
				{
					std::string memberNick = members[m];
					if (!memberNick.empty() && memberNick[0] == '@')
						memberNick = memberNick.substr(1);
					int fd = serv.findFdByNickname(memberNick);
					if (fd != -1)
						serv.sendToClient(fd, kickMsg);
				}
				vec[i].kickFromChannel(userName);
				std::cout << HCYN << "Operator: " HBLU "[" HCYN  << oper << HBLU "]" HCYN  " kicked "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " from "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;
				vec[i].printStatus();
				return ;
			}
			else
			{
				serv.sendToClient(c.get_fd(), err_nosuchnick(userName));
				std::cout << HCYN << "User: "  HBLU "[" HCYN << userName <<  HBLU "]" HCYN " not in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;
			}
		}
		else
		{
			serv.sendToClient(c.get_fd(), err_chanoprivsneeded(oper, channelName));
			std::cout << HCYN << "User: "  HBLU "[" HCYN << oper << HBLU "]" HCYN  " not operator of "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;
		}
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
	{
		serv.sendToClient(c.get_fd(), err_nosuchchannel(oper, channelName));
		std::cout << HCYN << "Channel: "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " doesn't exist!" << std::endl;
	}
}

