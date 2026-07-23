#include "Channel.hpp"

Channel::Channel() : _chanName("Default Channel"), _topic("Default topic"), _key("Default key")
{
	std::cout << "Channel default constructor" << std::endl;
}

Channel::Channel(std::string name) : _chanName(name), _topic("Default topic"), _key("Default key")
{
	std::cout << "Channel constructor with name: " << name << std::endl;
}

Channel::Channel(std::string name, std::string topic) : _chanName(name), _topic(topic), _key("Default key")
{
	std::cout << "Channel constructor with name: " << name << std::endl;
	std::cout << "Topic: " << topic << std::endl;
}

Channel::Channel(std::string name, std::string topic, std::string key) : _chanName(name), _topic(topic), _key(key)
{
	std::cout << "Channel constructor with name: " << name << std::endl;
	std::cout << "Topic: " << topic << std::endl;
	std::cout << "Key: " << key << std::endl;
}

Channel::Channel(const Channel &other) : _chanName(other._chanName), _topic(other._topic), _key(other._key)
{
	std::cout << "Channel copy constructor with name: " << _chanName << std::endl;
	std::cout << "Topic: " << _topic << std::endl;
	std::cout << "Key: " << _key << std::endl;
}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		this->_chanName = other._chanName;
	//	this->_users = other._users;
	//	this->_operators = other._operators;
		this->_topic = other._topic;
	//	this->_kickedUsers = other._kickedUsers;
	//	this->_userLimit = other._userLimit;
		this->_key = other._key;
	//	this->_iMode = other._iMode;
	//	this->_tMode = other._tMode;
	//	this->_kMode = other._kMode;
	}
	std::cout << "Channel copy assignment with name: " << _chanName << std::endl;

	return (*this);
}

Channel::~Channel()
{
	std::cout << "Channel destructor with name: " << _chanName << std::endl;
}

std::string Channel::getName()
{
	return (_chanName);
}

std::string Channel::getTopic()
{
	return (_topic);
}

std::string Channel::getKey()
{
	return (_key);
}
