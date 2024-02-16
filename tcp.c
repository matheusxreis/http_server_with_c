
#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include"http.c"

void listen_server(char* host, int port){

  int s;   /// socket
  int ns; // socket connected to client
  int namelen; // length of client name 
  struct sockaddr_in server; // me
  struct sockaddr_in client; // client

  char buf[12];

  struct sockaddr_in ddserver;


  if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("err in connection");
    exit(4); 
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(host);

  /* binding socket with server */
  if(bind(s, (struct sockaddr *)&server, sizeof(server)) < 0){
    printf("err in binding");
    exit(3);
  }else {
    printf("Binded....\n");
  }

  /* listening */
  if(listen(s, 10)!=0){
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
    if(recv(ns, buf, sizeof(buf), 0)==-1) {
      printf("err receiving...");
      exit(6);
    }
    
     struct ReadResponse r;
     read(buf, &r);
     printf("olha o path %s\n", r.path);

     char response[100];
     respond(&r, response);

    /* sending message back */ 
    //char ooi[200] =  "HTTP/1.1 404 Not Found\r\n\n";
    if(send(ns, response, sizeof(response),0) < 0) {
      printf("err sending");
      exit(7);
    }
    printf("look at response => %s\n",response);
    //printf("dps\n");
    //memset(buf,0,strlen(buf));


  close(ns);
  close(s);
}
