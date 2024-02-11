//
// Created by ikarimullin on 15.01.2024.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "squeeze.h"

#define CHARSET_SIZE 256

static const char *s1;
static const char *s2;

static char *result;

static int frequency[CHARSET_SIZE];

void doSqueeze(void);

void initFrequencyTable();

int squeeze_init(int argc, const char **argv) {
    if (argc < 1) {
        fprintf(stderr, "Usage: squeeze $string1 [$string2]");
        return -1;
    }
    s1 = argv[0];
    if (argc > 1) {
        s2 = argv[1];
    } else {
        s2 = NULL;
    }
    return 0;
}

void squeeze(void) {
    initFrequencyTable();
    doSqueeze();
    printf("%s\n", result);
    free(result);
}

void initFrequencyTable() {
    if (s2 != NULL) {
        char c;
        for (int i = 0; (c = s2[i]) != '\0'; ++i) {
            frequency[c]++;
        }
    }
}

void doSqueeze(void) {
    result = malloc(sizeof(char) * strlen(s1));
    char c;
    int j = 0;
    int i = 0;
    for (; (c = s1[i]) != '\0'; ++i) {
        if (!frequency[c]) {
            result[j++] = c;
        }
    }
    result[j] = '\0';
}


