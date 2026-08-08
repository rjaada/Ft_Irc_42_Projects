#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <unistd.h>
# include <sstream>
# include "../Includes/Colors.hpp"
# include "../Includes/Parser.hpp"
# include "../Includes/Replies.hpp"

class client;
class server;

class Channel
{
	private:

		std::string					_chanName;
		std::vector<std::string>	_users;
		std::vector<std::string>	_operators;
		std::vector<std::string>	_kickedUsers;
		std::string					_topic;
		std::string					_key;
		size_t						_userLimit;
		bool						_iMode;
		bool						_tMode;
		bool						_kMode;

	public:

		Channel();
		Channel(std::string name);
		Channel(std::string name, std::string topic);
		Channel(std::string name, std::string topic, std::string key);
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);
		~Channel();

		std::string					getName();
		std::vector<std::string>	getUsers();
		std::vector<std::string>	getOps();
		std::vector<std::string>	getKicked();
		std::string					getTopic();
		std::string					getKey();
		size_t						getLimit();
		int							isModeI();
		int							isModeT();
		int							isModeK();

		int							findInVec(std::vector<std::string> vec, std::string find); //find in vector, return 1 or 0
		void						addToVec(std::vector<std::string> &vec, std::string add); //add to vector
		void						removeFromVec(std::vector<std::string> &vec, std::string rem); //remove from vector
		void						printVector(std::vector<std::string> vec);

		void						invitedToChannel(std::string newUser);
		void						joinChannel(std::string	newUser);
		void						partFromChannel(std::string user);
		void						kickFromChannel(std::string user);
		void						becomeChannelOper(std::string user);
		void						removeChannelOper(std::string user);
		void						changeChannelTopic(std::string newTopic);

		void						handleMode(std::string mode, std::string param, client &c, server &serv);
		void						handleModeI(std::string mode);
		void						handleModeT(std::string mode);
		void						handleModeK(std::string mode, std::string key);
		void						handleModeO(std::string mode, std::string newOper, client &c, server &serv);
		void						handleModeL(std::string mode, std::string limit);

		void						printStatus();
		std::string					getChanInfo();
};

int	getFromServChanListPos(std::vector<Channel> &vec, std::string find);
int	findInServChanList(std::vector<Channel> vec, std::string find);
int	findInChanUserList(std::vector<std::string> vec, std::string find);

#endif