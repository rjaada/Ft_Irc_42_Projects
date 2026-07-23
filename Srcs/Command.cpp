#include "Command.hpp"

Command::Command(std::string type, std::string rawStr) : _commType(type),  _rawStr(rawStr)
{
	std::cout << "Command constructor with commType: " << _commType << std::endl;
	std::cout << "rawStr: " << _rawStr << std::endl;
}

Command::Command(const Command &other) : _commType(other._commType), _rawStr(other._rawStr)
{
	std::cout << "Command copy constructor with  commType: " << _commType << std::endl;
	std::cout << "rawStr: " << _rawStr << std::endl;
}

Command &Command::operator=(const Command &other)
{
	if (this != &other)
	{
		this->_rawStr = other._rawStr;
		this->_commType = other._commType;
	//	this->_commParaVals = other._commParaVals
	}
	std::cout << "Command copy assignment with commType: " << _commType << std::endl;
	std::cout << "rawStr: " << _rawStr << std::endl;

	return (*this);
}

Command::~Command()
{
	std::cout << "Command destructor with commType: " << _commType << std::endl;
	std::cout << "rawStr: " << _rawStr << std::endl;
}

std::string Command::getRawStr()
{
	return (_rawStr);
}

std::string Command::getCommType()
{
	return (_commType);
}
/*
?? Command::getParams()
{

}
*/
