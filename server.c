#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 0x901f //8080

void main(){
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  const struct sockaddr_in addr = {
	AF_INET,
	PORT,
	0
  };

  printf("Binding...\n");
  int bindReturn = bind(sockfd, &addr, sizeof(addr));
  if(bindReturn != 0){
     printf("Error binding");
     return;
  }

  printf("Listening for connections on PORT 8080...\n");
  listen(sockfd, 10);

  while(1){

    int client_fd = accept(sockfd, 0, 0);

    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    //GET /file.html ...
    //char* f = buffer + 5;
    //*strchr(f, ' ') = 0;
    //printf("Opening file %s...\n", f);
    //int opened_fd = open(f, O_RDONLY);

    char* c = "HTTP/1.1 200 OK\n\nHello, World!"; 

    //printf("Sending file...\n");
    //sendfile(client_fd, opened_fd, 0, 256);
    send(client_fd, c, strlen(c), 0);
  
    //close(opened_fd);
    close(client_fd);

  }
  close(sockfd); 
}
