#include "Channel.hpp"

Channel::Channel() : _chanName("Channel"), _topic("Default topic"), _key("Default key"), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name) : _chanName(name), _topic("Default topic"), _key("Default key"), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name, std::string topic) : _chanName(name), _topic(topic), _key("Default key"), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name, std::string topic, std::string key) : _chanName(name), _topic(topic), _key(key), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(const Channel &other) : _chanName(other._chanName), _topic(other._topic), _key(other._key), _userLimit(other._userLimit), _iMode(other._iMode), _tMode(other._tMode), _kMode(other._kMode)
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
	if (_iMode == true)
		return (1);
	else
		return (0);
}

int Channel::isModeT()
{
	if (_tMode == true)
		return (1);
	else
		return (0);
}

int Channel::isModeK()
{
	if (_kMode == true)
		return (1);
	else
		return (0);
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

void Channel::printStatus()
{
	std::cout << YEL"\n+++++++++++" HYEL "CHANNEL" YEL "+" HYEL "INFO" YEL "++++++++++++++" reset << std::endl;
	std::cout << HYEL"name:" YEL " [" HYEL << _chanName << YEL "]" reset << std::endl;
	std::cout << HYEL"topic:" YEL "  [" HYEL<< _topic << YEL "]" reset << std::endl;
	std::cout << YEL"-------------" HYEL "USER" YEL "-" HYEL "LIST" YEL "---------------" HYEL << std::endl;
	printVector(_users);
	std::cout << YEL"-------------" HYEL "OPERATORS" YEL "---------------" HYEL << std::endl;
	printVector(_operators);
	std::cout << YEL"------------" HYEL "KICKED" YEL "-" HYEL "USERS" YEL "-------------" HYEL << std::endl;
	printVector(_kickedUsers);
	std::cout << YEL"----------------" HYEL "MODE" YEL "-----------------" reset << std::endl;
	std::cout << HYEL"invite only:" YEL "  [" HYEL << _iMode << YEL "]" reset << std::endl;
	std::cout << HYEL"topic restriction:" YEL "  [" HYEL << _tMode << YEL "]" reset << std::endl;
	std::cout << HYEL"key protected:" YEL "  [" HYEL << _kMode << YEL "]" reset << std::endl;
	std::cout << HYEL"key:" YEL "  [" HYEL<< _key << YEL "]" reset << std::endl;
	std::cout << HYEL"user limit:" YEL "  [" HYEL << _userLimit << YEL "]" reset << std::endl;
	std::cout << YEL"+++++++++++++++++++++++++++++++++++++" reset << std::endl;
}

void	Channel::joinChannel(std::string newUser)
{
	if (!isModeI())
	{
		if (findInVec(getKicked(), newUser))
		{
			std::cout << BLU << "user:" << newUser << " can't join, kicked from channel!" << std::endl;
			return ;
		}
		if (!findInVec(getUsers(), newUser))
		{
			addToVec(_users, newUser);
			std::cout << BLU << "user:" << newUser << " joined the channel!" << std::endl;	
		}
		else
			std::cout << BLU << "user:" << newUser << " already in channel!" << std::endl;
	}
	else
		std::cout << RED "ERROR: INVITE ONLY!" << std::endl;
}

void	Channel::partFromChannel(std::string user)
{

	if (findInVec(getUsers(), user))
	{
		removeFromVec(_users, user);
		std::cout << BLU << "user:" << user << " left channel!" << std::endl;	
	}
	else
		std::cout << BLU << "user:" << user << " already left channel!" << std::endl;
}

void	Channel::kickFromChannel(std::string user)
{
	if (!findInVec(getKicked(), user))
	{
		if (findInVec(getUsers(), user))
		{
			addToVec(_kickedUsers, user);
			removeFromVec(_users, user);
			std::cout << BLU << "user:" << user << " kicked from channel!" << std::endl;	
		}
		else
			
			std::cout << BLU << "user:" << user << " not in channel!" << std::endl;
	}
	else
		std::cout << BLU << "user:" << user << " already kicked from channel!" << std::endl;		
}
