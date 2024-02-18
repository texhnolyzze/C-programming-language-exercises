#include <string.h>
#include <stdbool.h>
#include "unity.h"
#include "clang_keyword_counter/clang_keyword_counter.h"
#include "utils/test_utils/test_utils.h"

void invoke_test_file(char *filename);

void assert_equal_count(const char *word, size_t count);

void setUp() {

}

void tearDown() {

}

void test_count_keywords() {
    invoke_test_file("test_1.txt");
    assert_equal_count("char", 3);
    assert_equal_count("const", 5);
    assert_equal_count("else", 12);
    assert_equal_count("if", 14);
    assert_equal_count("int", 4);
    assert_equal_count("return", 4);
    assert_equal_count("void", 2);
}

void invoke_test_file(char *filename) {
    stdin_from_file(filename);
    count_keywords();
}

void assert_equal_count(const char *word, size_t count) {
    bool found = false;
    for (int i = 0; i < n_keywords(); ++i) {
        if (strcmp(word, key_table[i].word) == 0) {
            TEST_ASSERT_EQUAL_size_t(count, key_table[i].count);
            found = true;
            break;
        }
    }
    if (!found) {
        TEST_FAIL_MESSAGE(word);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_count_keywords);
    return UNITY_END();
}