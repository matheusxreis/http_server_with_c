#include"response.h"
#include<string.h>

HttpResponse html(char* content){
  HttpResponse r;

  strcpy(r.content, content);
  r.header.contentLength = strlen(content);
  stpcpy(r.header.contentType, "text/html");
  r.status = OK;

  return r;
}
