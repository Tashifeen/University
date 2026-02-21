/* mf_log.c */
#include <stdio.h>
#include "mf_log.h"

FILE *l;  /* File-scoped */
extern struct conf c;  /* Shared across object files */

int log_init(void)
{
    l = fopen(c.logPath, "a");  /* append */
    return !l;
}
int log_end(void){return fclose(l);}
void log_write(char const *const msg){fprintf(l, "%s\n", msg);}
