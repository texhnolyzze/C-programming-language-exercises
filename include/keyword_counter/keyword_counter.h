//
// Created by ikarimullin on 15.02.2024.
//

#ifndef SANDBOXTEST_KEYWORD_COUNTER_H
#define SANDBOXTEST_KEYWORD_COUNTER_H

#include <corecrt.h>

#define MAXWORD 100

struct key {
    const char *word;
    size_t count;
};

extern struct key key_table[];

void count_keywords(void);

size_t n_keywords();

#endif //SANDBOXTEST_KEYWORD_COUNTER_H
