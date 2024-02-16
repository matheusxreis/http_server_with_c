#include"tcp.c"

#define HOST "0.0.0.0"
#define PORT 3000

int main(){
   
  
  while(1){
   
    char baseUrl[PATH_SIZE] = "/";
    char* content = "<h1>Hello World!</h1>";

    char testUrl[PATH_SIZE] = "/test";
    char* contentTest = "<h3>Testing....</h3>";

    char* contentNFound = "<h1>Oooops...</h1>";

    get(baseUrl, content);
    get(testUrl, contentTest);
    not_found(contentNFound);

    listen_server(HOST, PORT); 
   };
}

