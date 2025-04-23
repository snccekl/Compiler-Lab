#include "config.h"
#include <stdlib.h>
#include <string.h>

char* strdup(const char* s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char* copy = (char*)malloc(len);
    if (copy != NULL) {
        memcpy(copy, s, len);
    }
    return copy;
}
