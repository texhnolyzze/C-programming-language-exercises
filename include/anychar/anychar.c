#include <stdio.h>
#include <string.h>
#include "anychar.h"

#define CHARSET_SIZE 256

static const char *s1;
static const char *s2;

static int frequency[CHARSET_SIZE];

void initFrequency();

void doAnychar();

int anychar_init(int argc, const char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: anychar string1 string2");
        return -1;
    }
    s1 = argv[0];
    s2 = argv[1];
    return 0;
}

void anychar(void) {
    initFrequency();
    doAnychar();
}

void doAnychar() {
    size_t len = strlen(s1);
    char c;
    int found = -1;
    for (int i = 0; i < len; ++i) {
        c = s1[i];
        if (frequency[c]) {
            found = i;
            break;
        }
    }
    printf("%d", found);
}

void initFrequency() {
    char c;
    for (int i = 0; (c = s2[i]) != '\0'; ++i) {
        frequency[c]++;
    }
}
