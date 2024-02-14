//
// Created by ikarimullin on 14.02.2024.
//

#include <corecrt.h>

#ifndef SANDBOXTEST_KEYWORD_TOKENIZER_H
#define SANDBOXTEST_KEYWORD_TOKENIZER_H

/**
 * @brief Obtains next word from stdin (which expected to be a valid C program),
 * which starts with letter/_/$ and contains any combination of letter/digit/_/$ afterwards.
 * String literals and comments are skipped.
 * @param word Where to store found word
 * @param lim Maximum size of word
 * @return first character of found word or EOF if no word found and stdin contains no more characters
 */
int get_keyword(char *word, size_t lim);

#endif //SANDBOXTEST_KEYWORD_TOKENIZER_H
