#include "topicCommand.hpp"

topicCommand::topicCommand(std::string type, std::string rawStr) : _commType(type),  _rawStr(rawStr)
{}

topicCommand::topicCommand(const topicCommand &other) : _commType(other._commType), _rawStr(other._rawStr)
{}

topicCommand &topicCommand::operator=(const topicCommand &other)
{
	if (this != &other)
	{
		this->_rawStr = other._rawStr;
		this->_commType = other._commType;
	}
	return (*this);
}

topicCommand::~topicCommand()
{}

std::string topicCommand::getRawStr()
{
	return (_rawStr);
}

std::string topicCommand::getCommType()
{
	return (_commType);
}
//username is the one calling the command, params tell us if we are changing the topic or just calling it to be printed on screen
void	topicCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string newTopic, size_t params, client &c, server &serv)
{
	std::cout << HCYN << "----------------- In topicCommandExec ----------------" << std::endl;
	if(!findInServChanList(vec, channelName))
	{
		serv.sendToClient(c.get_fd(), err_nosuchchannel(userName, channelName));
		std::cout << HBLU "[" HCYN  << channelName <<  HBLU "]" HCYN " channel not on list!" << std::endl;
		return ;
	}
	else
	{
		int i = getFromServChanListPos(vec, channelName);
		if (i != -1)
		{
			if (findInChanUserList(vec[i].getUsers(), userName) || findInChanUserList(vec[i].getUsers(), '@' + userName))
			{
				if (params == 2)
				{
					if (!newTopic.empty() && newTopic[0] == ':')
						newTopic = newTopic.substr(1);
					if (vec[i].isModeT())
					{
						if (!findInChanUserList(vec[i].getOps(), '@' + userName))
						{
							serv.sendToClient(c.get_fd(), err_chanoprivsneeded(userName, channelName));
							std::cout <<  HBLU "[" HCYN << channelName <<  HBLU "]" HCYN " channel topic change is restricted!" << std::endl;
							return ;
						}
					}
					vec[i].changeChannelTopic(newTopic);
					std::vector<std::string> members = vec[i].getUsers();
					std::string topicMsg = ":" + userName + " TOPIC " + channelName
						+ " :" + newTopic + "\r\n";
					for (size_t m = 0; m < members.size(); m++)
					{
						std::string memberNick = members[m];
						if (!memberNick.empty() && memberNick[0] == '@')
							memberNick = memberNick.substr(1);
						int fd = serv.findFdByNickname(memberNick);
						if (fd != -1)
							serv.sendToClient(fd, topicMsg);
					}
					vec[i].printStatus();
					return ;
				}
				if (params == 1)
				{
					if (vec[i].getTopic().empty())
						serv.sendToClient(c.get_fd(), rpl_notopic(userName, channelName));
					else
						serv.sendToClient(c.get_fd(), rpl_topic(userName, channelName, vec[i].getTopic()));
					std::cout <<  HBLU "[" HCYN << channelName <<  HBLU "]" HCYN " topic: " << vec[i].getTopic() << std::endl;
					return ;
				}
			}
			else
			{
				serv.sendToClient(c.get_fd(), err_notonchannel(userName, channelName));
				std::cout << HCYN << "User: " HBLU "[" HCYN << userName <<  HBLU "]" HCYN  " cant get get the topic if not in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN << std::endl;
			}
		}
	}
}

