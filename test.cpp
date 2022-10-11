#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>



int main() {
  // Create a socket (IPv4, TCP)
  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(9999); // htons is necessary to convert a number to
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
    fd_set fdset, cpset;
    struct timeval tv;
  // Listen to port 9999 on any address
                                   // network byte order
  if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 10) < 0) {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  fcntl(sockfd, F_SETFL, O_NONBLOCK);
    int retval;
  std::string buff;
  char buffer[10];
  FD_ZERO(&fdset);
  int connection;
  while(true)
  {
    std::cout  << "select ...\n";
    FD_SET(sockfd, &fdset);
    retval = select(FD_SETSIZE, &fdset, NULL, NULL, 0);
    if (retval)
    {
      auto addrlen = sizeof(sockaddr);
      if (FD_ISSET(sockfd, &fdset))
      {
        std::cout << "Found\n";
        connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
        if (connection < 0) 
        {
            std::cout << "Failed to grab connection. errno: " << errno << std::endl;
            exit(EXIT_FAILURE);
        }
        fcntl(connection, F_SETFL, O_NONBLOCK);
        int bytesRead = 1;
        int read = 0;
        std::cout << "read" << std::endl;
        std::cout << bytesRead << std::endl;
        while ((bytesRead = recv(connection, buffer, 10, 0)) > 0)
        {
          buffer[10] = '\0';
          std::cout << "recv called : " << bytesRead << std::endl;
          buff += buffer;
          read += bytesRead;
        }

        std::cout << "The message was: \n" << buff;
        // Send a message to the connection

        // Close the connections
        //close(connection);
      }
    }
    else
    {
      std::cout << "Timeout ..." << std::endl;
      
    }
  }
}