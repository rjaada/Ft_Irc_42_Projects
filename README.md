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



RFC1459 Internet Relay Chat Protocol  [Link](https://www.rfc-editor.org/info/rfc1459/)

### What is IRC?

Internet Relay Chat or IRC is a text-based communication protocol on the Internet.
It offers real-time messaging that can be either public or private. Users can exchange direct messages and join group channels.
IRC clients connect to IRC servers in order to join channels. IRC servers are connected together to form a network.

## What is a server?


### Project requirements

You are required to develop an IRC server using the C++ 98 standard.
You must not develop an IRC client.
You must not implement server-to-server communication.
Your executable will be run as follows:
```
./ircserv <port> <password>
```
- port: The port number on which your IRC server will be listening for incoming IRC connections.

- password: The connection password. It will be needed by any IRC client that tries to connect to your server.

- The server must be capable of handling multiple clients simultaneously without hanging.

- Forking is prohibited. All I/O operations must be non-blocking.

- Only 1 poll() (or equivalent) can be used for handling all these operations (read, write, but also listen, and so forth).

- Several IRC clients exist. You have to choose one of them as a reference. Your reference client will be used during the evaluation process.

- Your reference client must be able to connect to your server without encountering any error.

- Communication between client and server has to be done via TCP/IP (v4 or v6).

- Using your reference client with your server must be similar to using it with any official IRC server. However, you only have to implement the 

following features:

- You must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using your reference client.

- All the messages sent from one client to a channel have to be forwarded to every other client that joined the channel.

- You must have operators and regular users.

- Then, you have to implement the commands that are specific to channel operators:

* KICK - Eject a client from the channel

* INVITE - Invite a client to a channel

∗ TOPIC - Change or view the channel topic

∗ MODE - Change the channel’s mode:

· i: Set/remove Invite-only channel

· t: Set/remove the restrictions of the TOPIC command to channel operators

· k: Set/remove the channel key (password)

· o: Give/take channel operator privilege

· l: Set/remove the user limit to channel

• Of course, you are expected to write a clean code.

To ensure that your server correctly processes all data sent to it, the following simple test using nc can be performed:
```
\$> nc -C 127.0.0.1 6667
com^Dman^Dd
\$>
```
Use ctrl+D to send the command in several parts: ’com’, then ’man’, then ’d\n’.

## Instructions

### Running the server

### Connecting to the server with the terminal

### Connecting to the server with the client

## Commands

### PASS
```
PASS <password>
```
### NICK
```
NICK <nickname>
```
### USER
```
USER <username> <hostname> <servername> :<realname>
```
### QUIT
```
QUIT
```
### JOIN
```
JOIN <channel>
JOIN <channel> <key>
```
### PART
```
PART <channel>
```
### INVITE
```
INVITE <nickname> <channel>
```
### KICK
```
KICK <channel> <user>
```
### TOPIC
```
TOPIC <channel>
TOPIC <channel> :<new_topic>
```
### PRIVMSG
```
PRIVMSG <receiver> :<message>
```
### MODE
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

Guides/tutorials/blogs about the project:

"Small IRC Server [ft_irc 42 The Network]" by Ahmed Fatir [Link](https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9)

"FT_IRC : Channels and Command Management" by Mohamed sarda [Link](https://medium.com/@mohamedsarda/ft-irc-channels-and-command-management-ff1ff3758a0b)

"Sockets and Network Programming in C" by Mia Combeau [Link](https://www.codequoi.com/en/sockets-and-network-programming-in-c/)

Useful ft_irc introduction guide by bhagenlo [Link](https://haglobah.github.io/Mastering-42/holy_graph/ft_irc.html)

"Things to know" + some blogposts of the process (incomplete) [Link](https://ircgod.com/docs/irc/to_know/)

"FT_IRC 42" YouTube playlist with useful videos [Link](https://www.youtube.com/playlist?list=PLHBVNH27RbWqGTL-AYMylWkNck45cxPnG)

"Come on bro, let's recode on Discord" video by Nathan [Link](https://www.youtube.com/watch?v=hDLvHKEASRE)

Useful info:

"What is a Socket?" [Link](https://www.tutorialspoint.com/unix_sockets/what_is_socket.htm)

"Beej's Guide to Network Programming" [Link](https://beej.us/guide/bgnet/html/)

"The official home of RFCs" [Link](https://www.rfc-editor.org/)

"Socket Programming in C++" [Link](https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/)

"Setting up a server using C++ sockets!" [Link](https://medium.com/@ahmadesekak/setting-up-a-server-using-c-sockets-124e404593c9)

"Socket Address Structure" [Link](https://hyjae.gitbooks.io/socket-programming/content/)

## AI Resources

[Claude](https://claude.ai)

We haved used AI Tools to help us develop our program by trying to understand concepts, explaining logic bugs and trying to fix some memory leaks.

