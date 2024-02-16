/*
 * TODO: read more about HTTP protocol
 * TODO: implement THREADS and ThreadPool
 */
#include "http.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include"helpers/response.c"

int currentPosition = 0;
RegisteredRoute inMemory[10];

void listen_http(int ns) {
   char buf[100];

   /* receiving message */
  if(recv(ns, buf, sizeof(buf), 0)==-1) {
      printf("err receiving...");
      exit(6);
    }

    HttpRequest req = convert_to_http_request(buf);

    HttpResponse res = handle(&req);

    char size_res = get_size_response(res);
    char response[get_size_response(res)];  //// --------> here possible problem


    convert_from_http_response(res, response);

    /* sending message back */ 
    if(send(ns, response, sizeof(response),0) < 0) {
      printf("err sending");
      exit(7);
    }
    printf("response => %s", response);
    memset(response, 0, strlen(response));
    memset(buf,0,strlen(buf));
}

/* 
 * TODO: create one function for each http verb
 */

void get(char* path, cb cb){
  register_route(GET, path, cb);
}
void post(char* path, cb cb){
  register_route(POST, path, cb);
}
void not_found(cb cb){
  char path[PATH_SIZE] = "/404";
  register_route(NONE, path, cb);
}

HttpResponse handle(HttpRequest* req) {

  if(req->method == GET){
   int index = find_route(GET, req->path);

   if(index!=-1) { 
      return inMemory[index].cb(req);
   }
  }
  else if(req->method == POST) {

  }
  else if(req->method == PUT){ 

  }
  else if(req->method == DELETE){

  }

  return inMemory[NOT_FOUND_POSITION].cb(req);
}

/* private functions */
static void register_route(enum METHOD method, char* path, cb cb){
 
  if(currentPosition>=9) { return; } 

  RegisteredRoute r;
  r.path = malloc(sizeof(path));
  r.cb = cb;

  stpcpy(r.path, path);
  r.method = method;

  if(method == NONE){
   inMemory[NOT_FOUND_POSITION] = r;
  }else {
   inMemory[currentPosition++] = r;
  }

}

static int find_route(enum METHOD method, char* path){
  for(int i=0; i<currentPosition;i++) {
      if(inMemory[i].method == method
          && strcmp(inMemory[i].path, path) == 0){
        return i;
      };
  }
  return -1;
}

/*  mappers */
static HttpRequest convert_to_http_request(char* buffer){
 
  HttpRequest req;
  char method[SIZE], path[SIZE], version[SIZE], host[SIZE], userAgent[SIZE];
  sscanf(buffer, "%s %s %s\n Host: %s\n User-Agent: %s", method, path, version, host, userAgent);
  printf("req => %s, %s, %s, %s %s\n", method, path, version, host, userAgent);

  
  if(strcmp(method, "GET") == 0) {
    req.method = GET;
  }
  else if(strcmp(method, "POST") == 0){
    req.method = POST;
  }
  else if(strcmp(method, "PUT") == 0){
    req.method = PUT;
  }
  else if(strcmp(method, "DELETE") == 0){
    req.method = DELETE;
  }


  strcpy(req.path, path);
  strcpy(req.headers.host, host);
  strcpy(req.headers.userAgent, userAgent);

  return req;
};

static int get_size_response(HttpResponse res) {
 
     char x[3000];
     return sprintf(x,
      "HTTP/1.1 %d OK\nServer: matheusxreis\nContent-Length: %d\nContent-Type: %s\n\n%s",
      res.status,
      res.header.contentLength,
      res.header.contentType,
      res.content
      );   
};

static void convert_from_http_response(HttpResponse res, char* s){

     sprintf(s,
      "HTTP/1.1 %d OK\nServer: matheusxreis\nContent-Length: %d\nContent-Type: %s\n\n%s",
      res.status,
      res.header.contentLength,
      res.header.contentType,
      res.content
      );

}


