#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <iostream>
# include <string>
# include <vector>

class Channel
{
	private:

		std::string					_chanName;
		std::vector<std::string>	_users; //add to using JOIN command, should start with the fist person creating it
		std::vector<std::string>	_operators; //add an operator using MODE <channnelname> +o <username>
		std::string					_topic; //change using TOPIC command, depending on the MODE -/+ t of channel 
		std::vector<std::string>	_kickedUsers; //add using KICK command
		size_t						_userLimit; //default limit at creation is 10, change using MODE <channnelname> +l <number>
		std::string					_key;	//channel password, change using MODE <channnelname> +k <new_key> to set key
		bool						_iMode;	//is invite only, change using MODE <channnelname> +i to set, -i to remove
		bool						_tMode;	//is topic restricted, change using MODE <channnelname> +t to set, -t to remove
		bool						_kMode;	//has key, change using MODE <channnelname> -k to remove

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
		std::string					getTopic();
		std::vector<std::string>	getKicked();
		size_t						getLimit();
		std::string					getKey();
		int							isModeI();
		int							isModeT();
		int							isModeK();
		//TO DO:
//1.
//funtion that will iterate and find a value in any of the vector attributes:
//return 1 if found
//return 0 if not found
//
//2.
//funtions that will change the true/false mode of the MODE attributes when MODE command is used
//
//3.
//funtions that will add or remove values to the vector attributes: users, operators and kicked users
//
//4.
//functions that will change key, userlimit or topic of channnel

};

#endif