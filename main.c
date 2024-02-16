#include<sys/socket.h>
#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char **argv){

  int s;   /// socket
  unsigned short port; // port number
  int ns; // socket connected to client
  int namelen; // length of client name 
  struct sockaddr_in server; // me
  struct sockaddr_in client; // client

  char buf[12];

  struct sockaddr_in ddserver;

  if(!argv[1]) {
    printf("necessary port number\n");
    exit(4);
  }
  port = atoi(argv[1]);

  if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("err in connection");
    exit(4); 
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr("0.0.0.0");

  /* binding socket with server */
  if(bind(s, (struct sockaddr *)&server, sizeof(server)) < 0){
    printf("err in binding");
    exit(3);
  }else {
    printf("Binded....\n");
  }

  /* listening */
  if(listen(s, 1)!=0){
    printf("err in listen");
  }else {
    printf("Listening......\n");
  }

  /* accepting connection */
  
  namelen = sizeof(client);
  if((ns = accept(s, (struct sockaddr*)&client, &namelen)) == -1){
    printf("err in accept");
    exit(5);
  }else {

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client.sin_addr, str, INET_ADDRSTRLEN);
    printf("Accepted.... %s has connected\n", str);
  }

  /* receiving message */
  while(recv(ns, buf, sizeof(buf), 0)>0) {
    printf("received.... %s\n", buf);
  /* sending message back */ 

    if(send(ns, buf, sizeof(buf),0) < 0) {
      printf("err sending");
      exit(7);
    }
    printf("dps\n");
    memset(buf,0,strlen(buf));
   }


  close(ns);
  close(s);

}

