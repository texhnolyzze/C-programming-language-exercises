#include "unity.h"
#include "clang_keyword_counter/clang_keyword_tokenizer.h"
#include "utils/test_utils/test_utils.h"

void invoke_test_file(char *filename);

void setUp() {

}

void tearDown() {

}

char word[1000];
int ret;

void test_count_keywords() {
    invoke_test_file("test_1.txt");
    TEST_ASSERT_EQUAL_INT(EOF, ret);
    TEST_ASSERT_EQUAL_STRING("", word);

    invoke_test_file("test_2.txt");
    TEST_ASSERT_EQUAL_INT('_', ret);
    TEST_ASSERT_EQUAL_STRING("_$my_Var", word);

    invoke_test_file("test_3.txt");
    TEST_ASSERT_EQUAL_INT('$', ret);
    TEST_ASSERT_EQUAL_STRING("$a", word);

    invoke_test_file("test_4.txt");
    TEST_ASSERT_EQUAL_INT('1', ret);
    TEST_ASSERT_EQUAL_STRING("1", word);
    ret = get_keyword(word, 1000);
    TEST_ASSERT_EQUAL_INT('/', ret);
    TEST_ASSERT_EQUAL_STRING("/", word);
    ret = get_keyword(word, 1000);
    TEST_ASSERT_EQUAL_INT('5', ret);
    TEST_ASSERT_EQUAL_STRING("5", word);
    ret = get_keyword(word, 1000);
    TEST_ASSERT_EQUAL_INT(EOF, ret);
    TEST_ASSERT_EQUAL_STRING("", word);

    invoke_test_file("test_5.txt");
    TEST_ASSERT_EQUAL_INT('_', ret);
    TEST_ASSERT_EQUAL_STRING("_bar123$", word);

    invoke_test_file("test_6.txt");
    TEST_ASSERT_EQUAL_INT('a', ret);
    TEST_ASSERT_EQUAL_STRING("abra_148", word);
}

void invoke_test_file(char *filename) {
    stdin_from_file(filename);
    ret = get_keyword(word, 1000);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_count_keywords);
    return UNITY_END();
}