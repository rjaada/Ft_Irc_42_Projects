#include "Channel.hpp"

Channel::Channel() : _chanName("Channel"), _topic("Default topic"), _key("Default key"), _userLimit(10),_iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name) : _chanName(name), _topic("Default topic"), _key("Default key"), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name, std::string topic) : _chanName(name), _topic(topic), _key("Default key"), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(std::string name, std::string topic, std::string key) : _chanName(name), _topic(topic), _key(key), _userLimit(10), _iMode(false), _tMode(false), _kMode(false)
{}

Channel::Channel(const Channel &other) : _chanName(other._chanName), _topic(other._topic), _key(other._key), _userLimit(other._userLimit), _iMode(other.iMode), _tMode(other.tMode), _kMode(other.kMode)
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
	return (_kickUsers);
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
//TO DO:
//1.
//funtion that will iterate and find a value in any of the vector attributes:
//return 1 if found
//return 0 if not found
//
//2.
//funtions that will change the true/false mode of the MODE attributes when MODE command is used
//
//3.
//funtions that will add or remove values to the vector attributes: users, operators and kicked users
//
//4.
//functions that will change key, userlimit or topic of channnel
