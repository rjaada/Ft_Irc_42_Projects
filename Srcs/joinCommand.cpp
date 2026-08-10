#include "joinCommand.hpp"

joinCommand::joinCommand(std::string type,
	std::string rawStr) : _commType(type), _rawStr(rawStr)
{
}

joinCommand::joinCommand(const joinCommand &other) : _commType(other._commType),
	_rawStr(other._rawStr)
{
}

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
{
}

std::string joinCommand::getRawStr()
{
	return (_rawStr);
}

std::string joinCommand::getCommType()
{
	return (_commType);
}

// Server::handleJoin sends the proper numeric replies (331/332/353/366)
// and the JOIN broadcast once this returns, so this only needs to create
// the channel; no client-facing text belongs here.
void	newChannel(std::vector<Channel> &vec, std::string userName,
		std::string channelName, client &c, server &serv)
{
	(void)c;
	(void)serv;
	if (!findInServChanList(vec, channelName))
	{
		Channel newChannel(channelName);
		newChannel.joinChannel( '@' + userName);
		newChannel.becomeChannelOper(userName);
		vec.push_back(newChannel);
		std::cout << HBLU "[" HCYN << channelName << HBLU "]" HCYN " channel created by " HBLU "[" HCYN << userName << HBLU "]" HCYN " !" << std::endl;
		newChannel.printStatus();
	}
}
// username is the one joining, sometimes needs key, sometimes its ignored
void	joinCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string key, client &c, server &serv)
{
	int	i;

	std::cout << HCYN << "----------------- In joinCommandExec ----------------" << std::endl;
	if (!findInServChanList(vec, channelName))
	{
		newChannel(vec, userName, channelName, c, serv);
	}
	else
	{
		i = getFromServChanListPos(vec, channelName);
		if (i != -1)
		{
			if (vec[i].isModeI())
			{
				std::cout << HBLU "[" HCYN << channelName << HBLU "]" HCYN " channel is invite only!" << std::endl;
				return ;
			}
			if (vec[i].isModeK())
			{
				if (vec[i].getKey() != key)
				{
					std::cout << HBLU "[" HCYN << channelName << HBLU "]" HCYN " channel is key restricted!" << std::endl;
					return ;
				}
			}
			if (findInChanUserList(vec[i].getKicked(), userName) || findInChanUserList(vec[i].getKicked(), '@' + userName))
			{
				serv.sendToClient(c.get_fd(), err_bannedfromchan(channelName));
				std::cout << HBLU "[" HCYN << userName << HBLU "]" HCYN " cannot join " HBLU "[" HCYN << channelName << HBLU "]" HCYN " because they have been kicked!" << std::endl;
				return ;
			}
			if (vec[i].getUsers().size() + 1 >= vec[i].getLimit())
			{
				serv.sendToClient(c.get_fd(), err_channelisfull(channelName));
				std::cout << HCYN << "User: "  HBLU "[" HCYN << userName << HBLU "]" HCYN " can't join because "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " has reached user limit!" << std::endl;
				return ;
			}
			if (!findInChanUserList(vec[i].getUsers(), userName) && !findInChanUserList(vec[i].getUsers(), '@' + userName))
				vec[i].joinChannel(userName);
			else
			{
				serv.sendToClient(c.get_fd(), err_useronchannel(c.get_nickname(), userName, channelName));
				std::cout << HBLU "[" HCYN << userName << HBLU "]" HCYN " already in channel " HBLU "[" HCYN << channelName << HBLU "]" HCYN " !" << std::endl;
				return ;
			}
			vec[i].printStatus();
		}
	}
}
