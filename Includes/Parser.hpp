#ifndef PARSER_HPP
# define PARSER_HPP
# include <iostream>
# include <string>

class Parser
{
	private:

		std::string	_rawStr;
	
	public:

		Parser();
		Parser(std::string rawInput);
		Parser(const Parser &other);
		Parser &operator=(const Parser &other);
		~Parser();

		std::string		getRawStr();
		std::string		trimStr(std::string inStr, std::string startStr, std::string endStr);
						// ^ returns substring between to given strings and/or chars, use for parsing the params
		int				isRawComm(); //confirm if rawStr starts with a command word
		std::string		getCommType(); //return the identified command type
		int				checkParams(std::string	commType); //confirm it has all necessary params before parsing
//		??				parseRaw(); // parse the confirmed command and its params ?? idk
//		std::string		getParams(); // breakdown rawStr into the params ?? idks
//		??				getComm(); // return something(?), it will contain the command with its params, use for execution later
		int				passParaCount(); //check for 1 space between PASS and the param, check for 1 param;
		int				nickParaCount(); // same
		int				userParaCount(); // 4 params
		int				joinParaCount(); // min 1 param, can be many
		int				partParaCount(); // same
		int				topicParaCount(); //min 1, max 2
		int				inviteParaCount(); // 2 param
		int				kickParaCount(); // min 2, max 3
		int				quitParaCount(); // 1 or 0 params
		int				modeParaCount(); // min 2
		int				privmsgParaCount(); // 3 params, or more?
};

#endif