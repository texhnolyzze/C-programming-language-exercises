#ifndef SANDBOXTEST_WORD_TOKENIZER_H
#define SANDBOXTEST_WORD_TOKENIZER_H

#include <corecrt.h>

struct word_tokenizer {

    /**
     * Current line number
     */
    size_t line_number;

    /**
     * Line number of word read by tokenizer
     */
    size_t word_line_number;

    /**
     * Number of word read by tokenizer
     */
    size_t words_read;

    /**
     * Maximum possible length of word
     */
    size_t max_word_len;

    /**
     * Last word read by tokenizer
     */
    char *word;

    size_t word_len;

    /**
     * Negative code means something went wrong
     * state = 1 means stdin contains no more characters
     */
    int state;
};

/**
 * @return word_tokenizer to split stdin into tokens
 */
struct word_tokenizer *word_tokenizer_create(size_t max_word_len);

/**
 * @param tokenizer word_tokenizer, whose allocated memory should be freed (as well as word)
 */
void word_tokenizer_free(struct word_tokenizer *tokenizer);

/**
 * Get next word from stdin.
 * Word is any sequence of characters, that starts with alphabet letter/digit.
 * Words are separated from each other by any space character.
 * @param tokenizer
 */
void word_tokenizer_next_word(struct word_tokenizer *tokenizer);

#endif //SANDBOXTEST_WORD_TOKENIZER_H
