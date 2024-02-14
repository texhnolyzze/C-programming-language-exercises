//
// Created by ikarimullin on 14.02.2024.
//

#include <ctype.h>
#include <stdio.h>
#include "keyword_tokenizer.h"

int skip_non_keyword_content();

int skip_space(int c);

int skip_preprocessor_directive(int c);

int get_keyword(char *word, size_t lim) {
    char *w = word;
    int c;
    while ((c = skip_non_keyword_content()) == 0) {
//      NOP
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c) && c != '_' && c != '$') {
        *w = '\0';
        return c;
    }
    while (--lim > 0) {
        c = getchar();
        if (!isalnum(c) && c != '_' && c != '$') {
            ungetc(c, stdin);
            break;
        } else {
            *w++ = c;
        }
    }
    *w = '\0';
    return word[0];
}

int skip_preprocessor_directive(int c) {
    while (isalpha(c = getchar()) || c == '_') {
//          NOP
    }
    return c;
}

int skip_space(int c) {
    while (isspace(c = getchar())) {
//      NOP
    }
    return c;
}

int skip_non_keyword_content() {
    int c = getchar();
    if (isspace(c)) {
        c = skip_space(c);
        ungetc(c, stdin);
        return 0;
    } else if (c == '#') {
        c = skip_preprocessor_directive(c);
        ungetc(c, stdin);
        return 0;
    } else if (c == '/') {
        c = getchar();
        if (c == '/') {
//          Single line comment
            while (true) {
                c = getchar();
                if (c == '\n' || c == EOF) {
                    break;
                }
            }
            return 0;
        } else if (c == '*') {
//          Multiline comment
            int prev = c;
            for (;;) {
                c = getchar();
                if (c == '/' && prev == '*' || c == EOF) {
                    break;
                }
                prev = c;
            }
            return 0;
        } else {
            ungetc(c, stdin);
            return '/';
        }
    } else if (c == '"') {
//      String literal
        int prev = c;
        for (;;) {
            c = getchar();
            if (c == '"' && prev != '\\' || c == EOF) {
                break;
            }
            prev = c;
        }
        return 0;
    } else {
        return c;
    }
}
