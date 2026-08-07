#include "Channel.hpp"

Channel::Channel() : _chanName("Channel"), _users(), _operators(), _kickedUsers(), _topic("Default topic"), _key("Default key"), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name) : _chanName(name), _users(), _operators(), _kickedUsers(), _topic("Default topic"), _key("Default key"), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name, std::string topic) : _chanName(name), _users(), _operators(), _kickedUsers(), _topic(topic), _key("Default key"), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name, std::string topic, std::string key) : _chanName(name), _users(), _operators(), _kickedUsers(), _topic(topic), _key(key), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(const Channel &other) : _chanName(other._chanName), _users(other._users), _operators(other._operators), _kickedUsers(other._kickedUsers), _topic(other._topic), _key(other._key), _userLimit(other._userLimit), _iMode(other._iMode), _tMode(other._tMode), _kMode(other._kMode)
{}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		this->_chanName = other._chanName;
		this->_users = other._users;
		this->_operators = other._operators;
		this->_topic = other._topic;
		this->_kickedUsers = other._kickedUsers;
		this->_userLimit = other._userLimit;
		this->_key = other._key;
		this->_iMode = other._iMode;
		this->_tMode = other._tMode;
		this->_kMode = other._kMode;
	}
	return (*this);
}

Channel::~Channel()
{}

std::string Channel::getName()
{
	return (_chanName);
}

std::vector<std::string> Channel::getUsers()
{
	return (_users);
}

std::vector<std::string> Channel::getOps()
{
	return (_operators);
}

std::string Channel::getTopic()
{
	return (_topic);
}

std::vector<std::string> Channel::getKicked()
{
	return (_kickedUsers);
}

size_t Channel::getLimit()
{
	return (_userLimit);
}

std::string Channel::getKey()
{
	return (_key);
}

int Channel::isModeI()
{
	if (_iMode != true)
		return (0);
	else
		return (1);
}

int Channel::isModeT()
{
	if (_tMode != true)
		return (0);
	else
		return (1);
}

int Channel::isModeK()
{
	if (_kMode != true)
		return (0);
	else
		return (1);
}

int	Channel::findInVec(std::vector<std::string> vec, std::string find)
{
	for (size_t i = 0 ; i < vec.size() ; i++)
	{
		if (vec[i] == find)
			return (1);
	}
	return (0);
}

void Channel::addToVec(std::vector<std::string> &vec, std::string add)
{
	vec.push_back(add);
}

void Channel::removeFromVec(std::vector<std::string> &vec, std::string rem)
{
	for (size_t i = 0 ; i < vec.size() ; i++)
	{
		if (vec[i] == rem)
	    {
    	    vec.erase(vec.begin()+i);
    	}
    }
}

void Channel::printVector(std::vector<std::string> vec)
{
	for (size_t i = 0 ; i < vec.size() ; i++)
		std::cout << "[" << vec[i] << "]" << ' ';
	std::cout << '\n';
}

void	Channel::becomeChannelOper(std::string user)
{
	std::cout << HYEL << "--- In Channel::becomeChannelOper ---" << std::endl;
	if (findInVec(getKicked(), user))
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " can't become an operator, kicked from channel!" << std::endl;
		return ;
	}
	if (!findInVec(getUsers(), user) && !findInVec(getUsers(), '@' + user))
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " not in the channel!" << std::endl;
		return ;
	}
	if (!findInVec(getOps(), '@' + user))
	{
		addToVec(_operators, '@' + user);
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " is operator in the channel!" << std::endl;
		return ;
	}
	else
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " already a operator in the channel!" << std::endl;
}

void	Channel::removeChannelOper(std::string user)
{
	std::cout << HYEL << "--- In Channel::removeChannelOper ---" << std::endl;
	if (findInVec(getKicked(), user))
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " is a kicked user! Can't remove operator status!" << std::endl;
		return ;
	}
	if (!findInVec(getUsers(), user) && !findInVec(getUsers(), '@' + user))
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " not in the channel!" << std::endl;
		return ;
	}
	if (findInVec(getOps(), '@' + user))
	{
		removeFromVec(_operators, '@' + user);
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " is no longer operator in the channel!" << std::endl;
		return ;
	}
	else
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " is not even an operator in the channel! Can't remove operator status!" << std::endl;
}

void	Channel::invitedToChannel(std::string newUser)
{
	std::cout << HYEL << "--- In Channel::invitedToChannel ---" << std::endl;

	if (findInVec(getKicked(), newUser))
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newUser << HRED "]" HYEL  " can't be invited, kicked from channel!" << std::endl;
		return ;
	}
	if ((getUsers().size()) < getLimit())
	{
		if (!findInVec(getUsers(), newUser) && !findInVec(getUsers(), '@' + newUser))
		{
			addToVec(_users, newUser);
			std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newUser << HRED "]" HYEL  " joined the channel!" << std::endl;	
			return ;
	}
	else
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newUser << HRED "]" HYEL  " already in channel!" << std::endl;
	}
	else
	{
			std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newUser << HRED "]" HYEL  " can't join the channel! limit is " << getLimit() << std::endl;	
			return ;
	}
}

void	Channel::joinChannel(std::string newUser)
{
	std::cout << HYEL << "--- In Channel::joinChannel ---" << std::endl;
	if (!isModeI())
	{
		if (findInVec(getKicked(), newUser))
		{
			std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newUser << HRED "]" HYEL  " can't join, kicked from channel!" << std::endl;
			return ;
		}
		if ((getUsers().size()) < getLimit())
		{
			if (!findInVec(getUsers(), newUser) && !findInVec(getUsers(), '@' + newUser))
			{
				addToVec(_users, newUser);
				std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newUser << HRED "]" HYEL  " joined the channel!" << std::endl;	
				return ;
			}
			else
			std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newUser << HRED "]" HYEL  " already in channel!" << std::endl;
		}
		else
		{
				std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newUser << HRED "]" HYEL  " can't join the channel! limit is " << getLimit() << std::endl;	
				return ;
		}
	}
	else
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " ERROR: INVITE ONLY!" << std::endl;
}

void	Channel::partFromChannel(std::string user)
{
	std::cout << HYEL << "--- In Channel::partFromChannel ---" << std::endl;
	if (findInVec(getUsers(), user) || findInVec(getUsers(), '@' + user))
	{
		removeFromVec(_users, user);
		removeFromVec(_users, '@' + user);
			if (findInVec(getOps(), '@' + user))
				removeFromVec(_operators, '@' + user);
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " left channel!" << std::endl;	
	}
	else
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " in not even in channel!" << std::endl;
}

void	Channel::kickFromChannel(std::string user)
{
	std::cout << HYEL << "--- In Channel::kickFromChannel ---" << std::endl;
	if (!findInVec(getKicked(), user) && !findInVec(getKicked(), '@' + user))
	{
		if (findInVec(getUsers(), user) || findInVec(getUsers(), '@' + user))
		{
			addToVec(_kickedUsers, user);
			removeFromVec(_users, user);
			removeFromVec(_users, '@' + user);
				if (findInVec(getOps(), '@' + user))
					removeFromVec(_operators, '@' + user);
			std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL  " kicked from channel!" << std::endl;	
		}
		else
			
			std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << user << HRED "]" HYEL " not in channel!" << std::endl;
	}
	else
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL" user: "  HRED "[" HYEL << user << HRED "]" HYEL  " already kicked from channel!" << std::endl;		
}


void	Channel::changeChannelTopic(std::string newTopic)
{
	std::cout << HYEL << "--- In Channel::changeChannelTopic ---" << std::endl;
	_topic = newTopic;
	std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " new topic: " << getTopic() << std::endl;		
}

void	Channel::handleModeI(std::string mode)
{
	std::cout << HYEL << "--- In handleMode I ---" << std::endl;
	if(mode == "+i" && !isModeI())
	{
		_iMode = 1;
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " is set to invite only mode" << std::endl;
		return ;
	}
	else if(mode == "+i" && isModeI())
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " is already set to invite only mode!" << std::endl;
		return ;
	}
	else if(mode == "-i" && isModeI())
	{
		_iMode = 0;
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " removed invite only mode" << std::endl;
		return ;
	}
	else if (mode == "-i" && !isModeI())
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " already removed invite only mode!" << std::endl;
		return ;
	}
}

void	Channel::handleModeT(std::string mode)
{
	std::cout << HYEL << "--- In handleMode T ---" << std::endl;
	if(mode == "+t" && !isModeT())
	{
		_tMode = 1;
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " is now in topic restricted mode" << std::endl;
		return ;
	}
	else if(mode == "+t" && isModeT())
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " is already set to topic restricted mode!" << std::endl;
		return ;
	}
	else if(mode == "-t" && isModeT())
	{
		_tMode = 0;
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " removed topic restriction mode" << std::endl;
		return ;
	}
	else if(mode == "-t" && !isModeT())
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " already removed topic restriction mode!" << std::endl;
		return ;
	}
}

void	Channel::handleModeK(std::string mode, std::string key)
{
	std::cout << HYEL << "--- In handleMode K ---" << std::endl;
	if(mode == "+k")
	{
		_kMode = 1;
		_key = key;
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " is now in key restricted mode with key: " << key << std::endl;
		return ;
	}
	else if (mode == "-k" && isModeK())
	{
		_kMode = 0;
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " removed key restriction mode" << std::endl;
		return ;
	}
	else if (mode == "-k" && !isModeK())
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " already removed key restriction mode!" << std::endl;
		return ;
	}
}

void	Channel::handleModeO(std::string mode, std::string newOper)
{
	std::cout << HYEL << "--- In handleMode O ---" << std::endl;
	if (mode == "+o" && (!findInVec(_operators, '@' + newOper)))
	{
		removeFromVec(_users, newOper);
		addToVec(_users, '@' + newOper);
		addToVec(_operators, '@' + newOper);
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newOper << HRED "]" HYEL  " is now an operator in the channel"<< std::endl;
		return ;
	}
	else if (mode == "+o" && (findInVec(_operators, '@' + newOper) == 1))
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newOper << HRED "]" HYEL  " is already operator in the channel" << std::endl;
		return ;
	}
	if (mode == "-o" && (findInVec(_operators, '@' + newOper) == 1))
	{
		removeFromVec(_operators, '@' + newOper);
		removeFromVec(_users, '@' + newOper);
		addToVec(_users, newOper);
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newOper << HRED "]" HYEL  " is not an operator anymore in the channel"<< std::endl;
		return ;
	}
	else if (mode == "-o" && (!findInVec(_operators, '@' + newOper)))
	{
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user: "  HRED "[" HYEL << newOper << HRED "]" HYEL  " is already not an operator in channel" << std::endl;
		return ;
	}
}

void	Channel::handleModeL(std::string mode, std::string limit)
{
	std::cout << HYEL << "--- In handleMode L ---" << std::endl;
	if(mode == "+l")
	{
		int i = 0;
		while (limit[i])
		{
			if (!isdigit(limit[i]))
			{
				std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " Invalid user limit!" << std::endl;
				return ;
			}
			i++;
		}
		int	newLimit = atoi(limit.c_str());
		_userLimit = newLimit;
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName << HRED "]" HYEL " user limit is set to " << newLimit << std::endl;
		return ;
	}
	if(mode == "-l")
	{
		_userLimit = 10;
		std::cout << HYEL << "In channel: " HRED "[" HYEL << _chanName <<  HRED "]" HYEL  " user limit is set to default limit: " << _userLimit << std::endl;
		return ;
	}
}

void	Channel::handleMode(std::string mode, std::string param)
{
	std::cout << HYEL << "--- In handleMode ---" << std::endl;
	if (mode == "+i" || mode == "-i")
	{
		handleModeI(mode);
		return ;
	}
	if (mode == "+t" || mode == "-t")
	{
		handleModeT(mode);
		return ;
	}
	if (mode == "+k" || mode == "-k")
	{
		handleModeK(mode, param);
		return ;
	}
	if (mode == "+o" || mode == "-o")
	{
		handleModeO(mode, param);
		return ;
	}
	if (mode == "+l" || mode == "-l")
	{
		handleModeL(mode, param);
		return ;
	}
	else
		std::cout << HYEL << "In channel: " HRED "[" HYEL  << _chanName << " mode: "<< mode << " is not a valid mode!" << std::endl;
}

void	Channel::printStatus()
{
	std::cout << HRED"+++++++++++" HYEL "CHANNEL" HRED "+" HYEL "INFO" HRED "++++++++++++++" reset << std::endl;
	std::cout << HYEL"name:" HRED " [" HYEL << _chanName << HRED "]" reset << std::endl;
	std::cout << HYEL"topic:" HRED "  [" HYEL << _topic << HRED "]" reset << std::endl;
	std::cout << HRED"-------------" HYEL "USER" HRED "-" HYEL "LIST" HRED "---------------" HYEL << std::endl;
	printVector(_users);
	std::cout << HRED"-------------" HYEL "OPERATORS" HRED "---------------" HYEL << std::endl;
	printVector(_operators);
	std::cout << HRED"------------" HYEL "KICKED" HRED "-" HYEL "USERS" HRED "-------------" HYEL << std::endl;
	printVector(_kickedUsers);
	std::cout << HRED"----------------" HYEL "MODE" HRED "-----------------" reset << std::endl;
	std::cout << HYEL"invite only:" HRED "  [" HYEL << _iMode << HRED "]" reset << std::endl;
	std::cout << HYEL"topic restriction:" HRED "  [" HYEL << _tMode << HRED "]" reset << std::endl;
	std::cout << HYEL"key protected:" HRED "  [" HYEL << _kMode << HRED "]" reset << std::endl;
	std::cout << HYEL"key:" HRED "  [" HYEL<< _key << HRED "]" reset << std::endl;
	std::cout << HYEL"user limit:" HRED "  [" HYEL << _userLimit << HRED "]" reset << std::endl;
	std::cout << HRED"+++++++++++++++++++++++++++++++++++++" reset << std::endl;
}

std::string	Channel::getChanInfo()
{
	std::stringstream ss;

	ss << "+++++++++++"  "CHANNEL"  "+"  "INFO"  "++++++++++++++" << std::endl;
	ss << "name:"  " ["  << _chanName <<  "]" << std::endl;
	ss << "topic:"  "  ["  << _topic <<  "]" << std::endl;
	ss << "-------------"  "USER"  "-"  "LIST"  "---------------"  << std::endl;
	for (size_t i = 0 ; i < _users.size() ; i++)
		ss <<  "["  << _users[i] <<  "]" << ' ';
	ss << '\n';
	ss << "-------------"  "OPERATORS"  "---------------"  << std::endl;
	for (size_t i = 0 ; i < _operators.size() ; i++)
		ss <<  "["  << _operators[i] <<  "]" << ' ';
	ss << '\n';
	ss << "------------"  "KICKED"  "-"  "USERS"  "-------------"  << std::endl;
	for (size_t i = 0 ; i < _kickedUsers.size() ; i++)
		ss <<  "["  << _kickedUsers[i] <<  "]" << ' ';
	ss << '\n';
	ss << "----------------"  "MODE"  "-----------------" << std::endl;
	ss << "invite only:"  "  ["  << _iMode <<  "]" << std::endl;
	ss << "topic restriction:"  "  ["  << _tMode <<  "]" << std::endl;
	ss << "key protected:"  "  ["  << _kMode <<  "]" << std::endl;
	ss << "key:"  "  [" << _key <<  "]" << std::endl;
	ss << "user limit:"  "  ["  << _userLimit <<  "]" << std::endl;
	ss << "+++++++++++++++++++++++++++++++++++++" << std::endl;

	std::string s = ss.str();
	return (s);
}

int	getFromServChanListPos(std::vector<Channel> &vec, std::string find)
{
	for (size_t i = 0 ; i < vec.size() ; i++)
	{
		if (vec[i].getName() == find)
			return (i);
	}
	return (-1);
}

int	findInServChanList(std::vector<Channel> vec, std::string find)
{
	for (size_t i = 0 ; i < vec.size() ; i++)
	{
		if (vec[i].getName() == find)
			return (1);
	}
	return (0);
}

int	findInChanUserList(std::vector<std::string> vec, std::string find)
{
	for (size_t i = 0 ; i < vec.size() ; i++)
	{
		if (vec[i] == find || vec[i] == find)
			return (1);
	}
	return (0);
}


