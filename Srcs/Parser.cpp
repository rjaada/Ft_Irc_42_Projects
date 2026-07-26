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

std::string	commList[] = {"PASS", "NICK", "USER", "JOIN", "PART", "TOPIC", "INVITE", "KICK", "QUIT", "MODE", "PRIVMSG"};

int	Parser::isRawComm()
{
	if (_rawStr == "Empty")
		return (0);
	for (int i = 0; i < 11; i++)
	{
		std::size_t	found = _rawStr.find(commList[i]);
		if ((found != std::string::npos) && !(found > commList[i].size()))
		{
			if(_rawStr[0] != commList[i][0])
				return (0);
			return (1);
		}
	}
	return (0);
}

std::string	Parser::getCommType()
{
	for (int i = 0; i < 11; i++)
	{
		std::size_t	found = _rawStr.find(commList[i]);
		if ((found != std::string::npos) && !(found > commList[i].size()))
			return (commList[i]);
	}
	return ("not a command");
}

int	Parser::checkParams(std::string	commType)
{
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
	int	wFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if (isalnum(_rawStr[i]) && i != 0)
			{
				if (_rawStr[i - 1] == ' ')
					wFlag++;
			}
		}
	}
	if (sFlag == 1 && wFlag == 1)
		return (1);
	if (sFlag > 1)
		return (0);
	if ((sFlag == 1 && wFlag != 1) || (sFlag != 1 && wFlag != 1))
		return (-1);
	return (0);
}

int Parser::nickParaCount()
{
	int	sFlag = 0;
	int	wFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if (isalnum(_rawStr[i]) && i != 0)
			{
				if (_rawStr[i - 1] == ' ')
					wFlag++;
			}
		}
	}
	if (sFlag == 1 && wFlag == 1)
		return (1);
	if (sFlag > 1)
		return (0);
	if ((sFlag == 1 && wFlag != 1) || (sFlag != 1 && wFlag != 1))
		return (-1);
	return (0);
}

int Parser::userParaCount()
{
	int	sFlag = 0;
	int	wFlag = 0;
	int	colFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return(0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == ':') && i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (i + 1 <= strSize)
				if (_rawStr[i] == ':'&& _rawStr[i + 1])
					colFlag++;
		}
	}
	if (sFlag == 4 && wFlag == 4 && colFlag == 1)
		return (1);
	if (sFlag > 4 || (sFlag > wFlag + 1) || (sFlag > 0 && !wFlag) || !colFlag)
		return (0);
	if ((sFlag == 4 && wFlag != 4) || (sFlag != 4 && wFlag != 4))
		return (-1);
	return (0);
}

int Parser::joinParaCount()
{
	int	sFlag = 0;
	int	wFlag = 0;
	int	comFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if (strSize > 3)
		{
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if (_rawStr[i] == ',' && i != 0)
			{
				if (_rawStr[i - 1] == ' ' || !(i > 5) || _rawStr[i - 1] == ',')
					return (0);
				comFlag++;
			}
			if (isalnum(_rawStr[i]) && i != 0)
			{
				if ((_rawStr[i - 1] == ',') || ( _rawStr[i - 1] == ' '))
					wFlag++;
			}
			if (_rawStr[strSize - 1] == ' ' || _rawStr[strSize - 1] == ',')
				return (0);
		}
	}
	if ((sFlag == 1 && (wFlag == 1 && !comFlag)) || (sFlag == 2 && (wFlag >= 4 && comFlag >= 2)))
		return (1);
	if ((sFlag != 1 && !wFlag) || (sFlag != 2 && wFlag != 1) || (!_rawStr[4]))
		return (-1);
	if (sFlag > 2 || (comFlag >= wFlag))
		return (0);
	return (0);
}
//////////////////////////////////vvv IGNORE!!!!! !vvv/////////////////////////////////////////////////////
int Parser::partParaCount()
{
	int	sFlag = 0;
	int	wFlag = 0;
	int	comFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if (strSize > 3)
		{
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if (_rawStr[i] == ',' && i != 0)
			{
				if (_rawStr[i - 1] == ' ' || !(i > 5) || _rawStr[i - 1] == ',')
					return (0);
				comFlag++;
			}
			if (isalnum(_rawStr[i]) && i != 0)
			{
				if ((_rawStr[i - 1] == ',') || ( _rawStr[i - 1] == ' '))
					wFlag++;
			}
			if (_rawStr[strSize - 1] == ' ' || _rawStr[strSize - 1] == ',')
				return (0);
		}
	}
	if (sFlag == 1 && ((wFlag == 1 && !comFlag) || (wFlag && comFlag)))
		return (1);
	if ((sFlag != 1 && !wFlag) || (!_rawStr[4]))
		return (-1);
	if (sFlag > 1 || (comFlag >= wFlag))
		return (0);
	return (0);
}

int Parser::topicParaCount()
{
	int	sFlag = 0;
	int	wFlag = 0;
	int	colFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return(0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == ':') && i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (_rawStr[i] == ':')
			{
				if (strSize == i + 1)
					return (0);
				colFlag++;
			}
		}
	}
	if ((sFlag == 2 && wFlag == 2 && colFlag == 1) || (sFlag == 1 && wFlag == 1 && !colFlag))
		return (1);
	if (sFlag > 2 || (sFlag > wFlag + 1) || (sFlag > 0 && !wFlag) || colFlag > 1)
		return (0);
	if ((sFlag == 2 && wFlag != 2) || (sFlag != 2 && wFlag != 2))
		return (-1);
	return (0);
}

int Parser::inviteParaCount()
{
	int	sFlag = 0;
	int	wFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if (isalnum(_rawStr[i]) && i != 0)
			{
				if (_rawStr[i - 1] == ' ')
					wFlag++;
			}
		}
		if ((sFlag > 2 && !wFlag) || (_rawStr[6] != ' '))
			return (0); 
	}
	if (sFlag == 2 && wFlag == 2)
		return (1);
	if (sFlag > 2 || (sFlag > wFlag))
		return (0);
	if ((sFlag == 2 && wFlag != 2) || (sFlag != 2 && wFlag != 2))
		return (-1);
	return (0);
}

int Parser::kickParaCount()
{
	int	sFlag = 0;
	int	wFlag = 0;
	int	colFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return(0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == ':') && i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (_rawStr[i] == ':')
			{
				if (strSize == i + 1)
					return (0);
				colFlag++;
			}
			if ((sFlag > 2 && !wFlag) || (_rawStr[4] != ' '))
				return (0); 
		}
	}
	if ((sFlag == 3 && wFlag == 3 && colFlag == 1) || (sFlag == 2 && wFlag == 2 && !colFlag))
		return (1);
	if (sFlag > 3 || (sFlag > wFlag + 1) || (sFlag > 0 && !wFlag) || colFlag > 1)
		return (0);
	if ((sFlag == 3 && wFlag != 3) || (sFlag != 3 && wFlag != 3))
		return (-1);
	return (0);
}
/////////////////////////////////////////^^^ UGLYYYYYY ^^^//////////////////////////////////////////
int Parser::quitParaCount()
{
	int	sFlag = 0;
	int	wFlag = 0;
	int	colFlag = 0;
	size_t	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize ; i++)
	{
		if(_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return(0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == ':') && i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (_rawStr[i] == ':')
			{
				if (!_rawStr[i + 1])
					return (0);
				colFlag++;
			}
		}
	}
	if ((sFlag == 1 && wFlag == 1 && colFlag == 1) || ((!sFlag && !wFlag && !colFlag) && strSize == 4))
		return (1);
	if (sFlag > 1 || (sFlag > 1 && !wFlag) || colFlag > 1 || (strSize > 4 && !sFlag))
		return (0);
	if ((sFlag == 1 && wFlag != 1) || (sFlag != 1 && wFlag != 1) || (strSize > 4 && sFlag))
		return (-1);
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

std::vector<std::string> Parser::parseStr(std::string str, std::string delim)
{
	std::vector<std::string> ret;
	size_t	start = 0;
	if (!str.empty())
	{
		while(1)
		{
			size_t i = str.find(delim, start);
			if (i == std::string::npos)
				break;
			size_t len = i - start;
			ret.push_back(str.substr(start, len));
			start += (len + delim.size());
		}
		ret.push_back(str.substr(start));
	}
	return (ret);
}

void Parser::parseStart()
{
	std::cout << HMAG "----------ParseStart-------------" << std::endl;
	if (_rawStr.empty())
		std::cout << RED << "_rawStr is empty" << std::endl;
	if (isRawComm())
	{
		std::cout << HBLU "-----getCommType-----" << std::endl;
		std::string	type =  getCommType();
		std::cout << "Type is: "<< type << std::endl;
		std::cout << HCYN "-----checkParams-----" << std::endl;
		int	confirm = checkParams(type);
		if (confirm == 1)
		{
			std::cout << "Params: good!" << std::endl;
			std::cout << HGRN "-----parseStr--------" << std::endl;
			_params = parseStr(_rawStr, " ");
			for (std::string n : _params) //////////for testing
				std::cout << "[" << n << "]" << ' ';
			std::cout << '\n';
		}
		if(confirm == -1)
			std::cout << RED << type << " 461 ERR_NEEDMOREPARAMS :Not enough parameters" << std::endl;
		if (confirm == 0)
			std::cout << RED << type << " 420 ERR_INVALIDPARAMS :Invalid parameters" << std::endl;
	}		// invalid params (other error i just made up cuz why not)
	else
		std::cout << HYEL "_rawStr: " << _rawStr << " is not a command." << std::endl;
}