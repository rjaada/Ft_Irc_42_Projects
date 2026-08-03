#ifndef TOPICCOMMAND_HPP
# define TOPICCOMMAND_HPP
# include "Channel.hpp"

class topicCommand
{
	private:

		std::string	_commType;
		std::string	_rawStr;
	
	public:

		topicCommand(std::string type, std::string rawStr);
		topicCommand(const topicCommand &other);
		topicCommand &operator=(const topicCommand &other);
		~topicCommand();

		std::string			getRawStr();
		std::string			getCommType();

};

void	topicCommandExec(std::vector<Channel> &vec, std::string userName, std::string channelName, std::string newTopic, size_t params);

#endif