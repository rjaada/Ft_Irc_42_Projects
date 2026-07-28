#ifndef PARSER_HPP
# define PARSER_HPP
# include <iostream>
# include <string>
# include <vector>
# include "Colors.hpp" //makes text pretty ^ u ^

class Parser
{
	private:

		std::string	_rawStr;
		std::vector<std::string> _params; //params store here, starts will the command itself.
	
	public:

		Parser();
		Parser(std::string rawInput);
		Parser(const Parser &other);
		Parser &operator=(const Parser &other);
		~Parser();


		void						parseStart();
		std::string					getRawStr();
		std::string					trimStr(std::string inStr, std::string startStr, std::string endStr);
		int							isRawComm(); //confirm if rawStr starts with a command word
		std::string					getCommType(); //return the identified command type
		int							checkParams(std::string	commType); //confirm it has all necessary params before parsing
		std::vector<std::string>	parseStr(std::string str, std::string delim, std::string strFlag); // parse and return a vector with params
		int							passParaCount();
		int							nickParaCount();
		int							userParaCount();
		int							joinParaCount();
		int							partParaCount();
		int							topicParaCount();
		int							inviteParaCount();
		int							kickParaCount();
		int							quitParaCount();
		int							modeParaCount();
		int							privmsgParaCount();
};

#endif