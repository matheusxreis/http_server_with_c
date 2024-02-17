
#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include"http_server/http.c"
#include "http_server/http.h"
#include<pthread.h>

void listen_server(char* host, int port){

  int s;   /// socket
  int ns; // socket connected to client
  int namelen; // length of client name 
  struct sockaddr_in server; // me
  struct sockaddr_in client; // client

  char buf[100];

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
  }

  /* listening */
  if(listen(s, 10)!=0){
    printf("err in listen");
  }else {
    printf("******* ^----^ ********\n ****** WELCOME ******\nServer is listening in %s:%d\n", host, port);
  }

  /* accepting connection */
  
  while(1){
    namelen = sizeof(client);
    if((ns = accept(s, (struct sockaddr*)&client, &namelen)) == -1){
      printf("err in accept");
      exit(5);
    }else {
      char str[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, &client.sin_addr, str, INET_ADDRSTRLEN);
      printf("%s has connected\n", str);
    }
    /* http handling starts here */
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &listen_http, ns);
 } 
  close(s);
  close(ns);

}
