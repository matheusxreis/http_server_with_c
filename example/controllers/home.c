
#ifndef HTML_SERVER
#include"../../http_server/http.c"
#endif


HttpResponse Home(HttpRequest* req) {
  char* content = "<h1>Welcome to my website!</h1>";
  HttpResponse res = html(content);
  ///////res.status = 200;
  return res;
};
