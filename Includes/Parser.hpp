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
		std::vector<std::string>	parseStr(std::string str, std::string delim); // parse and return a vector with params
		int							passParaCount(); //check for 1 space between PASS and the param, check for 1 param
		int							nickParaCount(); // same
		int							userParaCount(); // 4 params + ':' befor last param
		///////////////////////////// vvv decide how complex the commands params will be b4 finishing these
		int							joinParaCount(); // min 1 param, can be many
		int							partParaCount(); // same
		int							topicParaCount(); //min 1, max 2, if 2 it needs ':'
		int							inviteParaCount(); // 2 param
		int							kickParaCount(); // min 2, max 3, if 3 it need ':'
		int							quitParaCount(); // 1 or 0 params, if 1 it need ':'
		int							modeParaCount(); // min 2
		int							privmsgParaCount(); // 3 params, or more? need ':'
};

#endif