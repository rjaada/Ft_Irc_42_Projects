#include "Parser.hpp"

Parser::Parser() : _rawStr("Empty"), _isCommand(0)
{
}

Parser::Parser(std::string rawInput) : _rawStr(rawInput), _isCommand(0)
{
}

Parser::Parser(const Parser &other) : _rawStr(other._rawStr),
	_params(other._params), _isCommand(other._isCommand)
{
}

Parser &Parser::operator=(const Parser &other)
{
	if (this != &other)
	{
		this->_rawStr = other._rawStr;
		this->_params = other._params;
		this->_isCommand = other._isCommand;
	}
	return (*this);
}

Parser::~Parser()
{
}

std::string Parser::getRawStr()
{
	return (_rawStr);
}

std::string commList[] = {"PASS", "NICK", "USER", "JOIN", "PART", "TOPIC",
	"INVITE", "KICK", "QUIT", "MODE", "PRIVMSG", "OPER"};

int Parser::isRawComm()
{
	if (_rawStr == "Empty")
		return (0);
	for (int i = 0; i < 12; i++)
	{
		std::size_t found = _rawStr.find(commList[i]);
		if ((found != std::string::npos) && !(found > commList[i].size()))
		{
			if (_rawStr[0] != commList[i][0])
				return (0);
			return (1);
		}
	}
	return (0);
}

std::string Parser::getCommType()
{
	for (int i = 0; i < 12; i++)
	{
		std::size_t found = _rawStr.find(commList[i]);
		if ((found != std::string::npos) && !(found > commList[i].size()))
			return (commList[i]);
	}
	return ("not a command");
}

int Parser::checkParams(std::string commType)
{
	int (Parser::*paramType[12])() = {&Parser::passParaCount,
		&Parser::nickParaCount, &Parser::userParaCount, &Parser::joinParaCount,
		&Parser::partParaCount, &Parser::topicParaCount,
		&Parser::inviteParaCount, &Parser::kickParaCount,
		&Parser::quitParaCount, &Parser::modeParaCount,
		&Parser::privmsgParaCount, &Parser::operParaCount};
	for (int i = 0; i < 12; i++)
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
	int		sFlag;
	int		wFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
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
	int		sFlag;
	int		wFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if ((isalnum(_rawStr[i])) && i != 0)
			{
				if (_rawStr[i - 1] == ' ')
					wFlag++;
			}
		}
	}
	if (!sFlag && !wFlag)
		return (1);
	if ((sFlag == 1 && wFlag == 1) || (sFlag == 2 && wFlag == 2))
		return (1);
	if ((sFlag >= 1 && !wFlag) || (sFlag == 2 && wFlag == 1))
		return (-1);
	if (sFlag > 2 || wFlag > 2)
		return (0);
	return (0);
}

int Parser::userParaCount()
{
	int		sFlag;
	int		wFlag;
	int		colFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	colFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return (0);
				sFlag++;
			}
			if (_rawStr[i] != ' ' && i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (i + 1 <= strSize)
				if (_rawStr[i] == ':' && _rawStr[i + 1])
					colFlag++;
		}
	}
	if (sFlag == 4 && wFlag == 4 && colFlag == 1)
		return (1);
	if (sFlag > 4 || wFlag > 4 || colFlag > 1 || (sFlag == 4 && wFlag == 4
			&& !colFlag))
		return (0);
	if ((sFlag == wFlag - 1) || !colFlag)
		return (-1);
	return (0);
}

int Parser::joinParaCount()
{
	int		sFlag;
	int		wFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if ((isalnum(_rawStr[i]) || _rawStr[i] == '#') && i != 0)
			{
				if (_rawStr[i - 1] == ' ')
					wFlag++;
			}
		}
	}
	if ((sFlag == 1 && wFlag == 1) || (sFlag == 2 && wFlag == 2))
		return (1);
	if ((sFlag >= 1 && !wFlag) || (sFlag == 2 && wFlag == 1))
		return (-1);
	if (sFlag > 2 || wFlag > 2)
		return (0);
	return (0);
}

int Parser::partParaCount()
{
	int		sFlag;
	int		wFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if ((isalnum(_rawStr[i]) || _rawStr[i] == '#') && i != 0)
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

int Parser::topicParaCount()
{
	int		sFlag;
	int		wFlag;
	int		colFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	colFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 5)
		{
			if (strSize == 6 || isalnum(_rawStr[5]))
				return (0);
			if (_rawStr[5] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return (0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == ':' || _rawStr[i] == '#')
				&& i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (i + 1 <= strSize)
				if (_rawStr[i] == ':' && _rawStr[i + 1])
					colFlag++;
		}
	}
	if ((sFlag == 1 && wFlag == 1 && !colFlag) || (sFlag == 2 && wFlag == 2
			&& colFlag == 1))
		return (1);
	if (sFlag > 2 || wFlag > 2 || colFlag > 1 || (sFlag == 2 && wFlag == 2
			&& !colFlag))
		return (0);
	if ((sFlag == wFlag - 1) || !colFlag)
		return (-1);
	return (0);
}

int Parser::inviteParaCount()
{
	int		sFlag;
	int		wFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 6)
		{
			if (strSize == 7 || isalnum(_rawStr[6]))
				return (0);
			if (_rawStr[6] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if ((isalnum(_rawStr[i]) || _rawStr[i] == '#') && i != 0)
			{
				if (_rawStr[i - 1] == ' ')
					wFlag++;
			}
		}
	}
	if (sFlag == 2 && wFlag == 2)
		return (1);
	if (sFlag < 2 || wFlag < 2)
		return (-1);
	if ((sFlag == 2 && !wFlag) || (sFlag == wFlag - 1))
		return (0);
	return (0);
}

int Parser::kickParaCount()
{
	int		sFlag;
	int		wFlag;
	int		colFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	colFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return (0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == ':' || _rawStr[i] == '#')
				&& i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (i + 1 <= strSize)
				if (_rawStr[i] == ':' && _rawStr[i + 1])
					colFlag++;
		}
	}
	if ((sFlag == 2 && wFlag == 2 && !colFlag) || (sFlag == 3 && wFlag == 3
			&& colFlag == 1))
		return (1);
	if (sFlag > 3 || wFlag > 3 || colFlag > 1 || (sFlag == 3 && wFlag == 3
			&& !colFlag))
		return (0);
	if ((sFlag == wFlag - 1) || !colFlag)
		return (-1);
	return (0);
}

int Parser::quitParaCount()
{
	int		sFlag;
	int		wFlag;
	int		colFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	colFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return (0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == ':') && i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (i + 1 <= strSize)
				if (_rawStr[i] == ':' && _rawStr[i + 1])
					colFlag++;
		}
	}
	if ((!sFlag && !wFlag && !colFlag) || (sFlag == 1 && wFlag == 1
			&& colFlag == 1))
		return (1);
	if (sFlag > 2 || wFlag > 2 || colFlag > 1)
		return (0);
	return (0);
}

int Parser::modeParaCount()
{
	int		sFlag;
	int		wFlag;
	int		setRemFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	setRemFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !setRemFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return (0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == '+' || _rawStr[i] == '-'
					|| _rawStr[i] == '#') && i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !setRemFlag)
					wFlag++;
			}
			if (i + 1 <= strSize)
				if ((_rawStr[i] == '+' || _rawStr[i] == '-') && _rawStr[i + 1])
					setRemFlag++;
		}
	}
	if ((sFlag == 2 && wFlag == 2 && setRemFlag == 1))
		return (1);
	if (sFlag > 2 || wFlag > 2 || setRemFlag > 1 || (sFlag == 2 && wFlag == 2
			&& !setRemFlag))
		return (0);
	if ((sFlag == wFlag - 1) || !setRemFlag)
		return (-1);
	return (0);
}

int Parser::privmsgParaCount()
{
	int		sFlag;
	int		wFlag;
	int		colFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	colFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 7)
		{
			if (strSize == 8 || isalnum(_rawStr[7]))
				return (0);
			if (_rawStr[7] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ' && i != 0 && !colFlag)
			{
				if (_rawStr[i - 1] == ' ')
					return (0);
				sFlag++;
			}
			if ((isalnum(_rawStr[i]) || _rawStr[i] == ':' || _rawStr[i] == '#')
				&& i != 0)
			{
				if (_rawStr[i - 1] == ' ' && !colFlag)
					wFlag++;
			}
			if (i + 1 <= strSize)
				if (_rawStr[i] == ':' && _rawStr[i + 1])
					colFlag++;
		}
	}
	if ((sFlag == 2 && wFlag == 2 && colFlag == 1))
		return (1);
	if (sFlag > 2 || wFlag > 2 || colFlag > 1 || (sFlag == 2 && wFlag == 2
			&& !colFlag))
		return (0);
	if ((sFlag == wFlag - 1) || !colFlag)
		return (-1);
	return (0);
}

int Parser::operParaCount()
{
	int		sFlag;
	int		wFlag;
	size_t	strSize;

	sFlag = 0;
	wFlag = 0;
	strSize = _rawStr.size();
	for (size_t i = 0; i < strSize; i++)
	{
		if (strSize > 4)
		{
			if (strSize == 5 || isalnum(_rawStr[4]))
				return (0);
			if (_rawStr[4] != ' ')
				return (-1);
		}
		if (_rawStr[i])
		{
			if (_rawStr[i] == ' ')
				sFlag++;
			if ((isalnum(_rawStr[i])) && i != 0)
			{
				if (_rawStr[i - 1] == ' ')
					wFlag++;
			}
		}
	}
	if (sFlag == 2 && wFlag == 2)
		return (1);
	if (sFlag > 2)
		return (0);
	if ((sFlag == 2 && wFlag != 2) || (sFlag != 2 && wFlag != 2))
		return (-1);
	return (0);
}

std::vector<std::string> Parser::parseStr(std::string str, std::string delim,
	std::string strFlag)
{
	size_t	start;
	size_t	j;
	size_t	i;
	size_t	len;

	std::vector<std::string> ret;
	start = 0;
	j = 0;
	if (!str.empty())
	{
		while (1)
		{
			i = str.find(delim, start);
			j = str.find(strFlag);
			if (i == std::string::npos)
				break ;
			if ((j != std::string::npos))
			{
				if (i > j)
				{
					i = (str.find(strFlag, start));
					i--;
					delim = strFlag;
					len = i - start;
					ret.push_back(str.substr(start, len));
					start += (len + delim.size());
					return (ret);
				}
			}
			len = i - start;
			ret.push_back(str.substr(start, len));
			start += (len + delim.size());
		}
		ret.push_back(str.substr(start));
	}
	return (ret);
}
// get specific parameter by index
std::string Parser::getParam(size_t i)
{
	if (i <= _params.size())
		return (_params[i]);
	else
		return (NULL);
}
// 4 debugging
void Parser::printVector(std::vector<std::string> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << "[" << vec[i] << "]" << ' ';
	std::cout << '\n';
}
// confirmation after the parse
int Parser::getIsCommConfirm()
{
	return (_isCommand);
}

std::vector<std::string> Parser::getParamVec()
{
	return (_params);
}

void Parser::parseStart()
{
	int	confirm;

	std::cout << HMAG "------------parseStart---------------" << std::endl;
	std::cout << HMAG "raw input: " << _rawStr << std::endl;
	if (_rawStr.empty())
		std::cout << RED << "_rawStr is empty" << std::endl;
	if (isRawComm())
	{
		std::string type = getCommType();
		confirm = checkParams(type);
		// -2 == recognized command word, malformed params (distinct from
		// 0 == raw string isn't a known command at all)
		_isCommand = (confirm == 0) ? -2 : confirm;
		if (confirm == 1)
		{
			_params = parseStr(_rawStr, " ", ":");
		}
		if (confirm == -1)
			std::cout << RED << type << " 461 ERR_NEEDMOREPARAMS :Not enough parameters" << std::endl;
		if (confirm == 0)
			std::cout << RED << type << " 420 ERR_INVALIDPARAMS :Invalid parameters" << std::endl;
		// invalid params
	}
	else
	{
		_isCommand = 0;
		std::cout << HYEL "_rawStr: " << _rawStr << " is not a command." << std::endl;
	}
}

void Parser::printStatus()
{
	std::cout << MAG "\n+++++++++++" HMAG "COMMAND" MAG "+" HMAG "INFO" MAG "++++++++++++++" reset << std::endl;
	std::cout << HMAG "\nrawStr:" MAG " [" HMAG << _rawStr << MAG "]" reset << std::endl;
	std::cout << HMAG "\nisCommand:" MAG "  [" HMAG << _isCommand << MAG "]" reset << std::endl;
	std::cout << MAG "\n-------------" HMAG "PARAMETERS" MAG "--------------" HMAG << std::endl;
	printVector(_params);
	std::cout << MAG "\n+++++++++++++++++++++++++++++++++++++" reset << std::endl;
}
