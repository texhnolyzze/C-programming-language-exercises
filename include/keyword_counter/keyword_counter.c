//
// Created by ikarimullin on 15.02.2024.
//

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "keyword_counter.h"
#include "keyword_tokenizer.h"

struct key key_table[] = {
        "auto", 0,
        "break", 0,
        "case", 0,
        "char", 0,
        "const", 0,
        "continue", 0,
        "default", 0,
        "do", 0,
        "double", 0,
        "else", 0,
        "enum", 0,
        "extern", 0,
        "float", 0,
        "for", 0,
        "goto", 0,
        "if", 0,
        "int", 0,
        "long", 0,
        "register", 0,
        "return", 0,
        "short", 0,
        "signed", 0,
        "sizeof", 0,
        "static", 0,
        "struct", 0,
        "switch", 0,
        "typedef", 0,
        "union", 0,
        "unsigned", 0,
        "void", 0,
        "volatile", 0,
        "while", 0
};

int cmp(char *word, struct key key) {
    return strcmp(word, key.word);
}

void count_keywords(void) {
    for (int i = 0; i < N_KEYWORDS; ++i) {
        key_table[i].count = 0;
    }
    char *word = malloc((MAXWORD + 1) * sizeof(char));
    if (word == NULL) {
        printf("count_keywords: not enough memory");
        return;
    }
    while (get_keyword(word, MAXWORD) != EOF) {
        struct key *k = bsearch(word, key_table, N_KEYWORDS, sizeof(key_table[0]), (int (*)(const void *, const void *)) cmp);
        if (k != nullptr) {
            k->count++;
        }
    }
    for (int i = 0; i < N_KEYWORDS; ++i) {
        struct key key = key_table[i];
        if (key.count > 0) {
            printf("%4zu %s\n", key.count, key.word);
        }
    }
    free(word);
}

size_t n_keywords() {
    return N_KEYWORDS;
}
