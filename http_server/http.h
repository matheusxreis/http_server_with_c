#ifndef HTML_SERVER
#define HTML_SERVER

#define SIZE 20
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


struct HttpHeaderResponse {
  char contentType[10];
  unsigned int contentLength;
};
struct HttpHeaderRequest {
  char host[100];
  char acceptLanguage[100];
  char userAgent[100];

};

typedef struct { 
  struct HttpHeaderResponse header;
  char content[1000];
  enum STATUS status;
  enum METHOD method;
  char* path;
  char statusMessage[PATH_SIZE];
} HttpResponse;

typedef struct {
 enum METHOD method;
 char path[PATH_SIZE];
 struct HttpHeaderRequest headers;
} HttpRequest;


typedef HttpResponse (*cb)(HttpRequest* req);


typedef struct {
  char* path;
  enum METHOD method;
  cb cb;
} RegisteredRoute;

#define SIZE 12
#define PATH_SIZE 15
#define NOT_FOUND_POSITION 9




/* register_route() 
 * this register all possible routes in memory
 */
static void register_route(enum METHOD method, char* path, cb cb);
/* get() 
 * this register GET routes in memory
 */
void get(char* path, cb cb);

/* post() 
 * this register POST routes in memory
 */
void post(char* path, cb cb);

/* not_found() 
 * define not_found template
 * */
void not_found(cb cb);


/* find_route()
 * verify if a route exist or not
 */
static int find_route(enum METHOD method, char* path); 


/* convert_to_http_request()
 * read all buffer and convert to a HttpRequest struct
 */
static HttpRequest convert_to_http_request(char* buffer);

/* convert_from_http_response()
 * convert a HttpResponse type in a string
 */
static void convert_from_http_response(HttpResponse res, char* s);
static int get_size_response(HttpResponse res);  
/* handle()
 * handle with http request,
 * receive a request and return a response
 * */
HttpResponse handle(HttpRequest* req); 
/*
 * listen_http()
 * ns is the socket client connection
 * listen for http connection
 */
void listen_http(int ns);


#endif
