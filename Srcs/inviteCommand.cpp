#include "inviteCommand.hpp"

inviteCommand::inviteCommand(std::string type, std::string rawStr) : _commType(type),  _rawStr(rawStr)
{}

inviteCommand::inviteCommand(const inviteCommand &other) : _commType(other._commType), _rawStr(other._rawStr)
{}

inviteCommand &inviteCommand::operator=(const inviteCommand &other)
{
	if (this != &other)
	{
		this->_rawStr = other._rawStr;
		this->_commType = other._commType;
	}
	return (*this);
}

inviteCommand::~inviteCommand()
{}

std::string inviteCommand::getRawStr()
{
	return (_rawStr);
}

std::string inviteCommand::getCommType()
{
	return (_commType);
}
//username is the one invited, cuser is the one inviting
void        inviteCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string cUser, client &c, server &serv)
{
	std::cout << HCYN << "----------------- In inviteCommandExec ---------------" << std::endl;
	if(!findInServChanList(vec, channelName))
	{
		std::cout << HBLU "[" HCYN  << channelName << HBLU "]" HCYN  " channel not on list!" << std::endl;
		return ;
	}
	else
	{
		int i = getFromServChanListPos(vec, channelName);
		if (i != -1)
		{
			if (findInChanUserList(vec[i].getUsers(), userName))
			{
				std::cout << HCYN << "User: "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " is already in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel by user: "  HBLU "[" HCYN << cUser << HBLU "]" HCYN  << std::endl;
				return ;
			}
			if (findInChanUserList(vec[i].getKicked(), userName))
			{
				std::cout << HCYN << "User: "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " has already been kick from "  HBLU "[" HCYN << channelName << HBLU "]" << std::endl;
				serv.sendToClient(c.get_fd(), ":You can't invite ");
				serv.sendToClient(c.get_fd(), cUser);
				serv.sendToClient(c.get_fd(), " to ");
				serv.sendToClient(c.get_fd(), channelName);
				serv.sendToClient(c.get_fd(), "because they have been kicked from the channel!\n");
				return ;
			}
			if (findInChanUserList(vec[i].getUsers(), cUser))
			{
				vec[i].invitedToChannel(userName);
				std::cout << HCYN << "User: "  HBLU "[" HCYN << userName << HBLU "]" HCYN  " was invited to "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel by user: "  HBLU "[" HCYN << cUser << HBLU "]" HCYN  << std::endl;
				serv.sendToClient(c.get_fd(), ":You have invited ");
				serv.sendToClient(c.get_fd(), userName);
				serv.sendToClient(c.get_fd(), " to ");
				serv.sendToClient(c.get_fd(), channelName);
				serv.sendToClient(c.get_fd(), "\n");
				int	iUserFd = serv.findFdByNickname(userName);
				serv.sendToClient(iUserFd, ":You have been invited to ");
				serv.sendToClient(iUserFd, channelName);
				serv.sendToClient(iUserFd, " by ");
				serv.sendToClient(iUserFd, cUser);
				serv.sendToClient(iUserFd, ". Welcome!\n");
				vec[i].printStatus();
				return ;
			}
			else
			{
				std::cout << HCYN << "User: "  HBLU "[" HCYN << cUser << HBLU "]" HCYN " can't invite anybody because they are not in "  HBLU "[" HCYN << channelName << HBLU "]" HCYN  " channel!" << std::endl;
				return ;
			}
		}
	}
}

