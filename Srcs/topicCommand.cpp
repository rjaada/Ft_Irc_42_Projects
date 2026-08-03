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
void	topicCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string newTopic, size_t params)
{
	std::cout << HCYN << "----------------- In topicCommandExec ----------------" << std::endl;
	if(!findInServChanList(vec, channelName))
	{
		std::cout << HBLU "[" HCYN  << channelName <<  HBLU "]" HCYN " channel not on list!" << std::endl;
		return ;
	}
	else
	{
		int i = getFromServChanListPos(vec, channelName);
		if (i != -1)
		{
			if (findInChanUserList(vec[i].getUsers(), userName))
			{
				if (params == 2)
				{
					if (vec[i].isModeT())
					{
						if (!findInChanUserList(vec[i].getOps(), userName))
						{
							std::cout <<  HBLU "[" HCYN << channelName <<  HBLU "]" HCYN " channel topic change is restricted!" << std::endl;
							return ;
						}
					}
					vec[i].changeChannelTopic(newTopic);
					return ;
				}
				if (params == 1)
				{
					std::cout <<  HBLU "[" HCYN << channelName <<  HBLU "]" HCYN " topic: " << vec[i].getTopic() << std::endl;
					return ;
				}
			}
			else
				std::cout << HCYN << "User: " HBLU "[" HCYN << userName <<  HBLU "]" HCYN  " cant get get the topic if not in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN << std::endl;
		}
	}

}

