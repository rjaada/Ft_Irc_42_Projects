#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <iostream>
# include <string>

class Channel
{
	private:

		std::string	_chanName;
//		??			_users;
//		??			_operators;
		std::string	_topic;
//		??			_kickedUsers;
//		int			_userLimit; //decide on a max limmit?
		std::string	_key;	//channel password
//		bool		_iMode;	//is invite only
//		bool		_tMode;	//is topic restricted
//		bool		_kMode;	//has key
//		??			_oMode;	//?? idk what to do with this one?
//		??			_lMode;	//?? idk if necessary too?

	
	public:

		Channel();
		Channel(std::string name);
		Channel(std::string name, std::string topic);
		Channel(std::string name, std::string topic, std::string key);
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);
		~Channel();

		std::string		getName();
//		??				getUsers();
//		??				getOps();
		std::string		getTopic();
//		??				getKicked();
//		int				getLimit();
		std::string		getKey();
//		int				isModeI();
//		int				isModeT();
//		int				isModeK();
};

#endif