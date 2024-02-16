
#ifndef HTML_SERVER
#include"../http.h"
#endif

/* html() 
 * returns a template html
 */
HttpResponse html(char* content);

/* redirect()
 * returns a template from path
 */
HttpResponse redirect(char* path);

/* json()
 * returns a json
 */
HttpResponse json(char* json);
