#include "joinCommand.hpp"

joinCommand::joinCommand(std::string type, std::string rawStr) : _commType(type),  _rawStr(rawStr)
{}

joinCommand::joinCommand(const joinCommand &other) : _commType(other._commType), _rawStr(other._rawStr)
{}

joinCommand &joinCommand::operator=(const joinCommand &other)
{
	if (this != &other)
	{
		this->_rawStr = other._rawStr;
		this->_commType = other._commType;
	}
	return (*this);
}

joinCommand::~joinCommand()
{}

std::string joinCommand::getRawStr()
{
	return (_rawStr);
}

std::string joinCommand::getCommType()
{
	return (_commType);
}

void    newChannel(std::vector<Channel> &vec, std::string userName, std::string channelName)
{
	if(!findInServChanList(vec, channelName))
	{
		Channel newChannel(channelName);
		newChannel.joinChannel(userName);
		newChannel.becomeChannelOper(userName);
		vec.push_back(newChannel);
		std::cout << HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel created by " HBLU "[" HCYN << userName <<  HBLU "]" HCYN  " !" << std::endl;
	}
}
//username is the one joining, sometimes need key, sometimes its ignored
void        joinCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string key)
{
	std::cout << HCYN << "----------------- In joinCommandExec ----------------" << std::endl;
	if(!findInServChanList(vec, channelName))
	{
		newChannel(vec, userName, channelName);
	}
	else
	{
		int i = getFromServChanListPos(vec, channelName);
		if (i != -1)
		{
			if (vec[i].isModeI())
			{
				std::cout <<  HBLU "[" HCYN  << channelName << HBLU "]" HCYN  " channel is invite only!" << std::endl;
				return ;
			}
			if (vec[i].isModeK())
			{
				if (vec[i].getKey() != key)
				{
					std::cout <<  HBLU "[" HCYN  << channelName << HBLU "]" HCYN  " channel is key restricted!" << std::endl;
					return ;
				}
			}
			vec[i].joinChannel(userName);
		}
	}

}

