/* mf_log.h */
#include "mf_conf.h"

int log_init(void);
int log_end(void);
void log_write(char const *const msg);

/* New macro: expands to a message with the line number */
#define LOG(msg) do {                     \
    char _buf[256];                       \
    snprintf(_buf, sizeof _buf,           \
             "[line %d] %s", __LINE__, msg); \
    log_write(_buf);                      \
} while (0)

#define LOG_ERR(msg) do { \
    char _buf[256]; \
    snprintf(_buf, sizeof _buf, "[line %d] ERROR: %s", __LINE__, msg); \
    log_write(_buf); \
    fprintf(stderr, "%s\n", _buf); \ // fprintf(WHERE, FORMAT, VALUES...);
} while (0)

