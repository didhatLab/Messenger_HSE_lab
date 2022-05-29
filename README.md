# Messenger_HSE_lab

Simple messenger for chatting with friends in the command line; 
Written entirely in C using sockets;


## Commands for client:
 * /friends - show your friends list(old command from the oldest version, recommended to use /show friends);
 * /add friend - add new friend (you can add anyone, even unregistered users);
 * /dell friend - remove user from friends list;
 * /dell dialog - remove dialog with user (Also worth mentioning that dialog won't be deleted on the side of another user, all messages remain on the server archive); 
 * /send mess - send a message to someone (at the end of the message you should write "/end"); 
 * /show friends - show your friends list;
 * /show dialogs - show your dialogs list;  
 * /show dialog <userName> show your dialog with <userName>;    
 * /check - check for new messages on the server;
 * /exit - close the application;
  
  
## Technology used in the project:
  * C and some standard libraries;
  * SQLite;
  * sockets;
  * CMake;

    
## License

HSE

**Free Software, Hell Yeah!**
