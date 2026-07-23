#include "Parser.hpp"

Parser::Parser() : _rawStr("Empty")
{
	std::cout << "Parser default constructor with Empty rawInput" << std::endl;
}

Parser::Parser(std::string rawInput) : _rawStr(rawInput)
{
	std::cout << "Parser constructor with rawInput: " << rawInput << std::endl;
}

Parser::Parser(const Parser &other) : _rawStr(other._rawStr)
{
	std::cout << "Parser copy constructor with rawInput: " << _rawStr << std::endl;
}

Parser &Parser::operator=(const Parser &other)
{
	if (this != &other)
		this->_rawStr = other._rawStr;
	std::cout << "Parser copy assignment with rawInput: " << _rawStr << std::endl;

	return (*this);
}

Parser::~Parser()
{
	std::cout << "Parser destructor with rawInput: " << _rawStr << std::endl;
}

std::string Parser::getRawStr()
{
	return (_rawStr);
}

std::string Parser::trimStr(std::string inStr, std::string startStr, std::string endStr)
{
	int	startPos = inStr.find(startStr);
	int	endPos = inStr.find(endStr);
	std::string	outStr = inStr.substr(startPos, endPos - startPos + endStr.size()); 
	return (outStr);
}

std::string	commList[] = {"PASS", "NICK", "USER", "JOIN", "PART", "TOPIC", "INVITE", "KICK", "QUIT", "MODE", "PRIVMSG"};

int	Parser::isRawComm()
{
	std::cout << "---Parser isRawComm---" << std::endl;

	if (_rawStr == "Empty")
	{
		std::cout << "rawStr is Empty" << std::endl;
		return (0);
	}
	for (int i = 0; i < 11; i++)
	{
		std::size_t	found = _rawStr.find(commList[i]);
		std::cout << "find is: "<< found << std::endl;
		std::cout << "commList[i].size is: "<< commList[i].size() << std::endl;
		if ((found != std::string::npos) && !(found > commList[i].size()))
		{
			std::cout << "rawStr[0]: " << _rawStr[0] << "commList[i][0]:" << commList[i][0]<< std::endl;
			if(_rawStr[0] != commList[i][0])
				return (0);
			std::cout << "rawStr contains a [" << commList[i] << "] command" << std::endl;
			return (1);
		}
	}
	std::cout << "No command found in rawStr" << std::endl;
	return (0);
}

std::string	Parser::getCommType()
{
	std::cout << "---Parser getCommType---" << std::endl;

	for (int i = 0; i < 11; i++)
	{
		std::size_t	found = _rawStr.find(commList[i]);
		if ((found != std::string::npos) && !(found > commList[i].size()))
		{
			std::cout << "rawStr is a [" << commList[i] << "] type" << std::endl;
			return (commList[i]);
		}
	}
	std::cout << "Not a command" << std::endl;
	return ("not a command");
}

int	Parser::checkParams(std::string	commType)
{
	std::cout << "check params" << std::endl;
	int	(Parser::*paramType[11])() = {&Parser::passParaCount, &Parser::nickParaCount, &Parser::userParaCount, 
				&Parser::joinParaCount, &Parser::partParaCount, &Parser::topicParaCount, &Parser::inviteParaCount, &Parser::kickParaCount, 
				&Parser::quitParaCount, &Parser::modeParaCount, &Parser::privmsgParaCount};

	for (int i = 0; i < 11; i++)
	{
		if (commList[i] == commType)
		{
			return (this->*paramType[i])();
		}
	}
	return (0);
}
int Parser::passParaCount()
{
	int	sFlag = 0;
	for (size_t i = 0; i < _rawStr.size() ; i++)
	{
		if (_rawStr[i] == ' ')
			sFlag++;
	}
	if(sFlag != 1)
		return (0);

	std::size_t	space = _rawStr.find(" ");
	std::cout << "space is: " << space << std::endl;
	if ((space != std::string::npos) && !(space == 5))
	{
		std::cout << "space is in the right place "<< std::endl;
		if (isalnum(_rawStr[space + 1]))
		{
			std::cout << "not empty after space "<< std::endl;
			return (1);
		}
	}

	return (0);
}

int Parser::nickParaCount()
{
	return (0);
}

int Parser::userParaCount()
{
	return (0);
}

int Parser::joinParaCount()
{
	return (0);
}

int Parser::partParaCount()
{
	return (0);
}

int Parser::topicParaCount()
{
	return (0);
}

int Parser::inviteParaCount()
{
	return (0);
}

int Parser::kickParaCount()
{
	return (0);
}

int Parser::quitParaCount()
{
	return (0);
}

int Parser::modeParaCount()
{
	return (0);
}

int Parser::privmsgParaCount()
{
	return (0);
}