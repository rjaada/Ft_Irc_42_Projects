(WIP!!!!!!!)

_This project has been created as part of the 42 curriculum by rjaada and romorale._
# ft_irc

## Description

### Summary

This project is about creating your own IRC server.
You will use an actual IRC client to connect to your server and test it.
The Internet is governed by solid standard protocols that allow connected computers to interact with each other.
It’s always beneficial to understand these protocols.

### What is RFC?

An RFC stands for "Request for Comments". It is a formal type of text document used first by computer engineers to propose, discuss, and build rules and standards for how the internet works. We are using the RFC1459 Internet Relay Chat Protocol as a reference for this project.
It can be found here: [Link](https://www.rfc-editor.org/info/rfc1459/)

### What is IRC?

Internet Relay Chat or IRC is a text-based communication protocol on the Internet. 
It offers real-time messaging that can be either public or private. Users can exchange direct messages and join group channels.
IRC clients connect to IRC servers in order to join channels. IRC servers are connected together to form a network.

### What is a server?

In simple terms, a specialized computer or computer program that provides data, files, or services to other computers (called clients) over a network.
"What is a Server? (Deepdive)" by LiveOverFlow [Link](https://www.youtube.com/watch?v=VXmvM2QtuMU)


## Project requirements

You are required to develop an IRC server using the C++ 98 standard.
You must not develop an IRC client.
You must not implement server-to-server communication.

- The server must be capable of handling multiple clients simultaneously without hanging.
- Forking is prohibited. All I/O operations must be non-blocking.
- Only 1 poll() (or equivalent) can be used for handling all these operations (read, write, but also listen, and so forth).
- Several IRC clients exist. You have to choose one of them as a reference. Your reference client will be used during the evaluation process.
- Your reference client must be able to connect to your server without encountering any error.
- Communication between client and server has to be done via TCP/IP (v4 or v6).

Using your reference client with your server must be similar to using it with any official IRC server. However, you only have to implement the following features:
- You must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using your reference client.
- All the messages sent from one client to a channel have to be forwarded to every other client that joined the channel.
- You must have operators and regular users.
- Then, you have to implement the commands that are specific to channel operators:

  - KICK - Eject a client from the channel
  - INVITE - Invite a client to a channel
  - TOPIC - Change or view the channel topic
  - MODE - Change the channel’s mode:
    - i: Set/remove Invite-only channel
    - t: Set/remove the restrictions of the TOPIC command to channel operators
    - k: Set/remove the channel key (password)
    - o: Give/take channel operator privilege
    - l: Set/remove the user limit to channel
 
- Of course, you are expected to write a clean code.


To ensure that your server correctly processes all data sent to it, the following simple test using nc can be performed:
```
\$> nc -C 127.0.0.1 6667
com^Dman^Dd
\$>
```

## Instructions

### Running the server
To run the server.
```
./ircserv <port> <password>
```
- port: The port number on which your IRC server will be listening for incoming IRC connections.
- password: The connection password. It will be needed by any IRC client that tries to connect to your server.

### Connecting to the server with the terminal
In this example the port number is 6667 and password is "pass1", so we connect with:
```
nc -C 127.0.0.1 6667
```

To register in the server, use the commands PASS, NICK and USER in this order:
![terminal](https://github.com/rjaada/Ft_Irc_42_Projects/blob/main/imgs/terminal_connection_steps/step1.png)


To create or join a channel, use the command JOIN. Channel names should always start with '#'.
![terminal](https://github.com/rjaada/Ft_Irc_42_Projects/blob/main/imgs/terminal_connection_steps/step2.png)
User names starting with '@' are channel operators.


### Connecting to the server with the client
We are using Hexchat as the client. Open and go to Hexchat -> Network List. Add the new network name then click edit.
![hexchat](https://github.com/rjaada/Ft_Irc_42_Projects/blob/main/imgs/client_connection_steps/step1.png)


Change to localhost (127.0.0.1) and the port number (6667 in this example). Also fill in the password (pass1 in this example) and then close.
![hexchat](https://github.com/rjaada/Ft_Irc_42_Projects/blob/main/imgs/client_connection_steps/step2.png)


When back at the network list, select the server and click connect. You're now connected to the server.
![hexchat](https://github.com/rjaada/Ft_Irc_42_Projects/blob/main/imgs/client_connection_steps/step3.png)


Commands are typed out differently here. For example JOIN is /join. Also, you don't need to use the command PRIVMSG for messaging, just use the different chat windows to send messages or commands to specific channels or users.
![channel](https://github.com/rjaada/Ft_Irc_42_Projects/blob/main/imgs/channel/2.png)

## Commands

### PASS
The PASS command is used to set a 'connection password'. The password can and must be set before any attempt to register the connection is made.
```
PASS <password>
```
### NICK
Is used to give user a nickname or change the previous one. If a NICK message arrives at a server which already knows about an identical nickname for another client, a nickname collision occurs.
```
NICK <nickname>
NICK <new_nickname> <nickname> 
```
### USER
Is used at the beginning of connection to specify the username, hostname, servername and realname of the new user.
```
USER <username> <hostname> <servername> :<realname>
```
### QUIT
The server must close the connection to a client that used QUIT. 
```
QUIT
```
### JOIN
Is used by client to start listening a specific channel. Whether or not a client is allowed to join a channel is
checked only by the server the client is connected to.
```
JOIN <channel>
JOIN <channel> <key>
```
### PART
The PART message causes the client sending the message to be removed from the list of active users in a channel.
```
PART <channel>
```
### INVITE
Is used to invite users to a channel. The parameter <nickname> is the nickname of the person to be invited to the target channel <channel>.
```
INVITE <nickname> <channel>
```
### KICK
The KICK command can be used to forcibly remove a user from a channel. It 'kicks them out' of the channel (forced PART).
```
KICK <channel> <user>
```
### TOPIC
The TOPIC message is used to change or view the topic of a channel. The topic for channel <channel> is returned if there is no <topic> given. If the <topic> parameter is present, the topic for that channel will be changed, if the channel modes permit this action.
```
TOPIC <channel>
TOPIC <channel> :<new_topic>
```
### PRIVMSG
Is used to send private messages between users. <receiver> is the nickname of the receiver of the message. <receiver> can also be a channel.
```
PRIVMSG <receiver> :<message>
```
### MODE
It allows both usernames and channels to have their mode changed. These commands are specific to channel operators.
```
MODE <channel> (+/-)(i/t/k/o/l)

MODE <channel> +i
MODE <channel> -i

MODE <channel> +t
MODE <channel> -t

MODE <channel> +k <new_key>
MODE <channel> -k

MODE <channel> +o <user>
MODE <channel> -o <user>

MODE <channel> +l <limit>
MODE <channel> -l
```

## Resources

- Guides/tutorials/blogs about the project:

"Small IRC Server [ft_irc 42 The Network]" by Ahmed Fatir [Link](https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9) <br>
"FT_IRC : Channels and Command Management" by Mohamed sarda [Link](https://medium.com/@mohamedsarda/ft-irc-channels-and-command-management-ff1ff3758a0b) <br>
"Sockets and Network Programming in C" by Mia Combeau [Link](https://www.codequoi.com/en/sockets-and-network-programming-in-c/) <br>
Useful ft_irc introduction guide by bhagenlo [Link](https://haglobah.github.io/Mastering-42/holy_graph/ft_irc.html) <br>
"Things to know" + some blogposts of the process (incomplete) [Link](https://ircgod.com/docs/irc/to_know/) <br>
"FT_IRC 42" YouTube playlist with useful videos [Link](https://www.youtube.com/playlist?list=PLHBVNH27RbWqGTL-AYMylWkNck45cxPnG) <br>
"Come on bro, let's recode on Discord" video by Nathan [Link](https://www.youtube.com/watch?v=hDLvHKEASRE) <br>


- Useful info:

"What is a Socket?" [Link](https://www.tutorialspoint.com/unix_sockets/what_is_socket.htm) <br>
"Beej's Guide to Network Programming" [Link](https://beej.us/guide/bgnet/html/) <br>
"The official home of RFCs" [Link](https://www.rfc-editor.org/) <br>
"Socket Programming in C++" [Link](https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/) <br>
"Setting up a server using C++ sockets!" [Link](https://medium.com/@ahmadesekak/setting-up-a-server-using-c-sockets-124e404593c9) <br>
"Socket Address Structure" [Link](https://hyjae.gitbooks.io/socket-programming/content/) <br>

## AI Resources

[Claude](https://claude.ai)

We haved used AI Tools to help us develop our program by trying to understand concepts, explaining logic bugs and trying to fix some memory leaks.

