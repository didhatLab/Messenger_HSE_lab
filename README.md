# Messanger_HSE_lab

Simple messanger for chating with friends in the command line;\n
Written entierly in C using sockets;


Commands for client:
 /friends - show your friends list(old command from the oldest version, recommended to use /show frineds);
 /add friend - add new friend (you can add anyone, even unregistred users);
 /dell <optinally> {
    friend - remove user from friends list;
    dialog - remove dialog with user (Also worth mentioning, that dialogue isn't deleted from another user, messages also remain on the server archive);
  }
 /send mess - send a message to someone (at the end of the message you should write "/end"); 
 /show <optionally> {
    friends - show your friend list;
    dialogs - show your dialog list;
    dialog <usrName> show your dialog with somebody;
  }
 /check - check for new messgaes on the server;
 /exit - close the application;
  
  
Techologies used in the project:
  >C and some standard libraries;
  >SQLite;
  >sockects;
  >CMake;
