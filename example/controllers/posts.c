
#ifndef HTML_SERVER
#include"../../http_server/http.c"
#endif


HttpResponse Posts(HttpRequest* req) {

  char* content = "<h1>Posts</h1><ul><li>post 1</li><li>post 2</li><li>post 3</li><li>post 4</li><li>post 5</li><li>post 6</li><li>post 7</li>";
  HttpResponse res = html(content);
  ///////res.status = 200;
  return res;

};
