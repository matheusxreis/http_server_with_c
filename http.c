/*
 * TODO: read more about HTTP protocol
 * TODO: implement THREADS and ThreadPool
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 12
#define PATH_SIZE 15
#define NOT_FOUND_POSITION 9

enum METHOD {
  GET,
  POST,
  PUT,
  DELETE,
  NONE = -1
};

enum STATUS {
  OK = 200,
  CREATED = 201,
  NOT_FOUND = 404,
  BAD_REQUEST = 400
};


struct ReadResponse {
  enum METHOD method;
  char path[PATH_SIZE];
};

struct HttpHeader {
  char contentType[10];
  unsigned int contentLength;
};

typedef struct { 
  struct HttpHeader header;
  char content[100];
  enum STATUS status;
  enum METHOD method;
  char path[PATH_SIZE];
  char statusMessage[PATH_SIZE];
} HttpResponse;

int currentPosition = 0;
HttpResponse inMemory[10];

/* registering routes */
void register_route(enum METHOD method, char path[PATH_SIZE], char* content){
 
  if(currentPosition>=9) { return; } 

  HttpResponse r;

  stpcpy(r.path, path);
  stpcpy(r.content, content);
  stpcpy(r.header.contentType, "text/html");
  r.method = method;
  r.header.contentLength = strlen(content);

  if(method == NONE){
   inMemory[NOT_FOUND_POSITION] = r;
  }else {
   inMemory[currentPosition++] = r;
  }

}
/* registering get routes 
 * TODO: create one function for each http verb
 */
void get(char path[PATH_SIZE], char* content){
  register_route(GET, path, content);
};

/* registering not found path */
void not_found(char* content){
  char path[PATH_SIZE] = "/404";
  register_route(NONE, path, content);
};

/* finding a route */
static int find_route(enum METHOD method, char* path){
  for(int i=0; i<10;i++) {
      if(inMemory[i].method == method
          && strcmp(inMemory[i].path, path) == 0){
        return i;
      };
  }
  return -1;
}

/* handling with HTTP REQUEST 
 * TODO: create HttpRequest struct and update this
 * TODO: read + than one line from buffer
 */
void read(char* buffer, struct ReadResponse* r) {

  char method[SIZE], path[SIZE], version[SIZE];
  sscanf(buffer, "%s %s %s", method, path, version);

  if(strcmp(method, "GET") == 0) {
    r->method = GET;
  }
  else if(strcmp(method, "POST") == 0){
    r->method = POST;
  }
  else if(strcmp(method, "PUT") == 0){
    r->method = PUT;
  }
  else if(strcmp(method, "DELETE") == 0){
    r->method = DELETE;
  }

  stpcpy(r->path, path);
};

/* responding with HTTP RESPONSE 
 * TODO: receive from parameters a HttpRequest struct
 */
void respond(struct ReadResponse* read, char* response) {

  if(read->method == GET){
   int index = find_route(GET, read->path);

   if(index!=-1) { 
      sprintf(response,
      "HTTP/1.1 %d OK\nServer: matheusxreis\nContent-Length: %d\nContent-Type: %s\n\n%s",
      inMemory[index].status,
      inMemory[index].header.contentLength,
      inMemory[index].header.contentType,
      inMemory[index].content
      );
      return;
   }else{

      sprintf(response,
      "HTTP/1.1 %d OK\nServer: matheusxreis\nContent-Length: %d\nContent-Type: %s\n\n%s",
      OK,
      // inMemory[NOT_FOUND_POSITION].status,
      inMemory[NOT_FOUND_POSITION].header.contentLength,
      inMemory[NOT_FOUND_POSITION].header.contentType,
      inMemory[NOT_FOUND_POSITION].content
      );
      return;
   }

  }
  else if(read->method == POST) {

  }
  else if(read->method == PUT){

  }
  else if(read->method == DELETE){

  }


}
