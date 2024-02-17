#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include "word_tokenizer.h"

struct word_tokenizer *word_tokenizer_create(const size_t max_word_len) {
    struct word_tokenizer *tokenizer = malloc(sizeof(struct word_tokenizer));
    if (tokenizer == NULL) {
        fprintf(stderr, "word_tokenizer_create: not enough memory\n");
        return NULL;
    }
    tokenizer->state = 0;
    tokenizer->line_number = 1;
    tokenizer->words_read = 0;
    tokenizer->word_line_number = 1;
    tokenizer->max_word_len = max_word_len;
    tokenizer->word_len = 0;
    tokenizer->word = malloc((max_word_len + 1) * sizeof(char));
    if (tokenizer->word == NULL) {
        fprintf(stderr, "word_tokenizer_create: not enough memory\n");
        free(tokenizer);
        return NULL;
    }
    *tokenizer->word = '\0';
    return tokenizer;
}

void word_tokenizer_free(struct word_tokenizer *tokenizer) {
    if (tokenizer == NULL) {
        return;
    }
    if (tokenizer->word != NULL) {
        free(tokenizer->word);
    }
    free(tokenizer);
}

int skip_non_word_content(struct word_tokenizer *tokenizer, int *prev);

void word_tokenizer_next_word(struct word_tokenizer *tokenizer) {
    int c;
    int prev = -1;
    while ((c = skip_non_word_content(tokenizer, &prev)) == 0) {
//      NOP
    }
    if (c == EOF) {
        *tokenizer->word = '\0';
        tokenizer->word_len = 0;
        tokenizer->state = 1;
        return;
    }
    char *w = tokenizer->word;
    *w++ = c;
    size_t len = 1;
    tokenizer->word_line_number = tokenizer->line_number;
    while (len < tokenizer->max_word_len) {
        c = getchar();
        if (isspace(c)) {
            if (c == '\n') {
                tokenizer->line_number++;
            }
            break;
        } else if (c == EOF) {
            ungetc(c, stdin);
            break;
        } else {
            *w++ = c;
            len++;
        }
    }
    *w = '\0';
    tokenizer->word_len = len;
    tokenizer->words_read++;
}

int skip_non_word_content(struct word_tokenizer *tokenizer, int *prev) {
    int c = getchar();
    if (isspace(c)) {
        if (c == '\n') {
            tokenizer->line_number++;
        }
        *prev = c;
        return 0;
    } else if (c == EOF) {
        return c;
    } else if (!isalnum(c)) {
        *prev = c;
        return 0;
    } else {
        if (isspace(*prev) || *prev == -1) {
            *prev = c;
            return c;
        } else {
            *prev = c;
            return 0;
        }
    }
}
