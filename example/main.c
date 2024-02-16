#include"../tcp.c"
#include"controllers/controllers.c"

#define HOST "0.0.0.0"
#define PORT 3000

int main(){
     /* defining get routes */
     get("/", &Home); 
     get("/posts", &Posts); 
     /* starting the server */ 
     listen_server(HOST, PORT); 
}

