#include"tcp.c"

#define HOST "0.0.0.0"
#define PORT 3000


HttpResponse Home(HttpRequest* req) {

  char* content = "<h1>We gotta take the power back!</h1><img src=\"https://cdn-p.smehost.net/sites/7f9737f2506941499994d771a29ad47a/wp-content/uploads/2020/01/rage-against-the-machine.jpg\"/>";
  HttpResponse res = html(content);
  ///////res.status = 200;
  return res;
};

HttpResponse About(HttpRequest* req) {

  char* content = "<h1>By matheusxreis!</h1>";
  HttpResponse res = html(content);
  ///////res.status = 200;
  return res;
};

HttpResponse NotFound(HttpRequest* req) {

  char* content = "<h1>Ooooops =(</h1>";
  HttpResponse res = html(content);
  res.status = NOT_FOUND;// you can change response content this way
  return res;
};



int main(){
     /* defining get routes */
     get("/", &Home); 
     get("/about", &About);
     
     /* defing not found function */
     not_found(&NotFound);
     
     /* starting the server */ 
     listen_server(HOST, PORT); 
}

