#include <string.h>
#include "unity.h"
#include "utils/strings/strings.h"
#include "utils/word_tokenizer/word_tokenizer.h"
#include "utils/test_utils/test_utils.h"

void setUp() {

}

void tearDown() {

}

void test1() {
    stdin_from_file("test-1.txt");
    struct word_tokenizer *tokenizer = word_tokenizer_create(5);
    TEST_ASSERT_EQUAL_size_t(1, tokenizer->word_line_number);
    TEST_ASSERT_EQUAL_size_t(1, tokenizer->line_number);
    TEST_ASSERT_EQUAL_size_t(0, tokenizer->words_read);
    TEST_ASSERT_EQUAL_size_t(5, tokenizer->max_word_len);
    TEST_ASSERT_EQUAL_STRING("", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(0, tokenizer->word_len);

    word_tokenizer_next_word(tokenizer);

    TEST_ASSERT_EQUAL_STRING("abra", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(1, tokenizer->word_line_number);
    TEST_ASSERT_EQUAL_size_t(1, tokenizer->words_read);
    TEST_ASSERT_EQUAL_size_t(4, tokenizer->word_len);

    word_tokenizer_next_word(tokenizer);

    TEST_ASSERT_EQUAL_STRING("cada", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(2, tokenizer->word_line_number);
    TEST_ASSERT_EQUAL_size_t(2, tokenizer->words_read);
    TEST_ASSERT_EQUAL_size_t(4, tokenizer->word_len);

    word_tokenizer_next_word(tokenizer);

    TEST_ASSERT_EQUAL_STRING("bra", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(3, tokenizer->word_line_number);
    TEST_ASSERT_EQUAL_size_t(3, tokenizer->words_read);
    TEST_ASSERT_EQUAL_size_t(3, tokenizer->word_len);

    word_tokenizer_next_word(tokenizer);

    TEST_ASSERT_EQUAL_STRING("blabl", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(4, tokenizer->word_line_number);
    TEST_ASSERT_EQUAL_size_t(4, tokenizer->words_read);
    TEST_ASSERT_EQUAL_size_t(5, tokenizer->word_len);

    word_tokenizer_next_word(tokenizer);

    TEST_ASSERT_EQUAL_STRING("abaca", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(4, tokenizer->word_line_number);
    TEST_ASSERT_EQUAL_size_t(5, tokenizer->words_read);
    TEST_ASSERT_EQUAL_size_t(5, tokenizer->word_len);

    word_tokenizer_next_word(tokenizer);

    TEST_ASSERT_EQUAL_STRING("dabad", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(4, tokenizer->word_line_number);
    TEST_ASSERT_EQUAL_size_t(6, tokenizer->words_read);
    TEST_ASSERT_EQUAL_size_t(5, tokenizer->word_len);

    word_tokenizer_next_word(tokenizer);

    TEST_ASSERT_EQUAL_STRING("", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(6, tokenizer->words_read);
    TEST_ASSERT_EQUAL_INT(1, tokenizer->state);
    TEST_ASSERT_EQUAL_size_t(0, tokenizer->word_len);

    word_tokenizer_free(tokenizer);
}

void test2() {
    stdin_from_file("test-2.txt");
    struct word_tokenizer *tokenizer = word_tokenizer_create(5);
    while (true) {
        word_tokenizer_next_word(tokenizer);
        if (tokenizer->state == 1) {
            break;
        }
        size_t len = strlen(tokenizer->word);
        TEST_ASSERT_GREATER_OR_EQUAL_size_t(1, len);
        TEST_ASSERT_GREATER_OR_EQUAL_size_t(len, tokenizer->word_len);
    }
    TEST_ASSERT_EQUAL_size_t(1000, tokenizer->words_read);
}

void test3() {
    stdin_from_file("test-3.txt");
    struct word_tokenizer *tokenizer = word_tokenizer_create(5);
    word_tokenizer_next_word(tokenizer);
    TEST_ASSERT_EQUAL_STRING("abra", tokenizer->word);
    TEST_ASSERT_EQUAL_size_t(1, tokenizer->words_read);
    TEST_ASSERT_EQUAL_INT(0, tokenizer->state);
    TEST_ASSERT_EQUAL_size_t(5, tokenizer->word_line_number);
    word_tokenizer_next_word(tokenizer);
    TEST_ASSERT_EQUAL_size_t(1, tokenizer->words_read);
    TEST_ASSERT_EQUAL_INT(1, tokenizer->state);
    TEST_ASSERT_EQUAL_STRING("", tokenizer->word);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    return UNITY_END();
}