#include <stdlib.h>
#include "ferror.h"

void ErrorAndTerminate(const char *errmessage, unsigned int errorcode){
    printf("*** Termination due to error\n");
    printf("*** Message is: '%s'", errmessage);
    printf("*** Exiting with error code %u\n", errorcode);
    exit(errorcode);    
}
