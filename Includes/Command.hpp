#ifndef COMMAND_HPP
# define COMMAND_HPP
# include <iostream>
# include <string>

class Command
{
	private:

		std::string	_commType;
		std::string	_rawStr;
//		??			_commParaVals;
	
	public:

//		Command();
		Command(std::string type, std::string rawStr);
		Command(const Command &other);
		Command &operator=(const Command &other);
		~Command();

		std::string		getRawStr();
		std::string		getCommType();
//		??				getParams();
};

#endif