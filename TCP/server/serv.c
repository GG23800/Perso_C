#include<stdio.h>    
#include<stdlib.h> 
#include<sys/socket.h>    
#include<sys/types.h>    
#include<netinet/in.h>    
#include<error.h>    
#include<strings.h>    
#include<unistd.h>    
#include<arpa/inet.h>    

#include<signal.h> //to catch CTRL+C

#define ERROR -1    
#define MAX_CLIENTS 2    
#define MAX_DATA 250
#define PORT 7538

static int sock, new;

void signal_callback(int signum)
{
	printf("catch signal %d\n",signum);
	close (new);
	close (sock);
	exit(signum);
}

int main(int argc, char **argv)    
{    
 struct sockaddr_in server={0};    
 struct sockaddr_in client={0};    
    
 int sockaddr_len = sizeof(struct sockaddr_in);    
 int data_len;    
 char data[MAX_DATA+1]={0};
 const char * rep="ok, c'est noté";

 signal(SIGINT,signal_callback);

 if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)    
 {    
  perror("server socket: ");    
  exit(-1);    
 }    

 server.sin_family = AF_INET;    
 server.sin_port = htons(PORT);    
 server.sin_addr.s_addr = INADDR_ANY;    //allow all IP to access to the server
 bzero(&server.sin_zero, 8);    

 if((bind(sock, (struct sockaddr *)&server, sockaddr_len)) == ERROR)    
 {    
  perror("bind : ");    
  exit(-1);    
 }

 if((listen(sock, MAX_CLIENTS)) == ERROR)    
 {    
  perror("listen");    
  exit(-1);    
 }


// int k=1;
 while(1) // Better signal handling required    
 {    
  if((new = accept(sock, (struct sockaddr *)&client, &sockaddr_len)) == ERROR)    
  {    
   perror("accept");    
   exit(-1);    
  }    


  printf("New Client connected from port no %d and IP %s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));

  data_len = 1;            

  while(data_len)    
  {    
   data_len = recv(new, data, MAX_DATA+1, 0);
   printf("longueur=%d\n",data_len);    

   if(data_len)    
   {    
    //send(new, data, data_len, 0);    
    data[data_len] = '\0';    
    printf("Sent mesg: %s\n", data);
    send(new,rep,14,0);    
   }
  }

  printf("Client disconnected\n");

  close(new);
 // k=0;

 }

 close(sock);
 return 0;
}
