#include "modeCommand.hpp"

modeCommand::modeCommand(std::string type, std::string rawStr) : _commType(type),  _rawStr(rawStr)
{}

modeCommand::modeCommand(const modeCommand &other) : _commType(other._commType), _rawStr(other._rawStr)
{}

modeCommand &modeCommand::operator=(const modeCommand &other)
{
	if (this != &other)
	{
		this->_rawStr = other._rawStr;
		this->_commType = other._commType;
	}
	return (*this);
}

modeCommand::~modeCommand()
{}

std::string modeCommand::getRawStr()
{
	return (_rawStr);
}

std::string modeCommand::getCommType()
{
	return (_commType);
}
//cuser is the one using mode, param is the parameter after (+/-)(i/t/k/o/l), sometimes not needed
void        modeCommandExec(std::vector<Channel> &vec, std::string cUser, std::string channelName, std::string mode, std::string param, client &c, server &serv)
{
	std::cout << HCYN << "----------------- In modeCommandExec ----------------" << std::endl;
	if(!findInServChanList(vec, channelName))
	{
		serv.sendToClient(c.get_fd(), err_nosuchchannel(cUser, channelName));
		std::cout << HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel not on list!" << std::endl;
		return ;
	}
	else
	{
		int i = getFromServChanListPos(vec, channelName);
		if (i != -1)
		{
			if (findInChanUserList(vec[i].getUsers(), cUser) || findInChanUserList(vec[i].getUsers(), '@' + cUser))
			{
				if (findInChanUserList(vec[i].getOps(), '@' + cUser))
				{
					vec[i].handleMode(mode, param);
					std::cout << HCYN << "User: " HBLU "[" HCYN << cUser << HBLU "]" HCYN  " operator in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " changed the mode to: " << mode << std::endl;

					std::vector<std::string> members = vec[i].getUsers();
					std::string modeMsg = ":" + cUser + " MODE " + channelName
						+ " " + mode + (param.empty() ? "" : " " + param)
						+ "\r\n";
					for (size_t m = 0; m < members.size(); m++)
					{
						std::string memberNick = members[m];
						if (!memberNick.empty() && memberNick[0] == '@')
							memberNick = memberNick.substr(1);
						int fd = serv.findFdByNickname(memberNick);
						if (fd != -1)
							serv.sendToClient(fd, modeMsg);
					}
					vec[i].printStatus();
					return ;
				}
				else
				{
					serv.sendToClient(c.get_fd(), err_chanoprivsneeded(cUser, channelName));
					std::cout << HCYN << "User: " HBLU "[" HCYN << cUser << HBLU "]" HCYN  " is not an operator in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN << std::endl;
					return ;
				}
			}
			else
			{
				serv.sendToClient(c.get_fd(), err_notonchannel(cUser, channelName));
				std::cout << HCYN << "User: " HBLU "[" HCYN << cUser << HBLU "]" HCYN  " is not in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN << std::endl;
				return ;
			}
		}

	}
}

