#include <string.h>
#include <ctype.h>
#include "dcl_tokenizer.h"
#include "stdio.h"

int token_type;
char token[DCL_MAX_TOKEN + 1];

int get_token(void) {
    int c;
    char *token_ptr = token;
    while ((c = getchar()) == ' ' || c == '\t') {
//      NOP
    }
    if (c == '(') {
        while ((c = getchar()) == ' ' || c == '\t') {
//          NOP
        }
        if (c == ')') {
            strcpy(token, "()");
            return token_type = PARENS;
        } else {
            ungetc(c, stdin);
            strcpy(token, "(");
            return token_type = '(';
        }
    } else if (c == '[') {
        *token_ptr++ = c;
        while (true) {
            if (token_ptr - token == DCL_MAX_TOKEN) {
                printf("Token to big (max len %d): %s.\n", DCL_MAX_TOKEN, token);
                *token = '\0';
                return token_type = INVALID;
            }
            c = getchar();
            if (c == ']') {
                *token_ptr++ = c;
                break;
            } else if (c == ' ' || c == '\t') {
                continue;
            } else if (c == EOF || !isdigit(c)) {
                printf("invalid character after [: '%c'\n", (char) c);
                *token = '\0';
                return token_type = INVALID;
            }
            *token_ptr++ = c;
        }
        *token_ptr = '\0';
        return token_type = BRACKETS;
    } else if (isalpha(c)) {
        *token_ptr++ = c;
        while (true) {
            c = getchar();
            if (isalnum(c)) {
                if (token_ptr - token == DCL_MAX_TOKEN) {
                    printf("Token to big (max len %d): %s.\n", DCL_MAX_TOKEN, token);
                    *token = '\0';
                    return token_type = INVALID;
                }
                *token_ptr++ = c;
            } else {
                break;
            }
        }
        *token_ptr = '\0';
        ungetc(c, stdin);
        if (strcmp("const", token) == 0) {
            return token_type = CONST;
        } else {
            return token_type = NAME;
        }
    } else {
        token[0] = c;
        token[1] = '\0';
        return token_type = c;
    }
}
