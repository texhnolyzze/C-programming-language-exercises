#include "unity.h"
#include "dcl/dcl_tokenizer.h"
#include "utils/test_utils/test_utils.h"

void invoke_test_file(char *filename);

void setUp() {

}

void tearDown() {

}

void test_count_keywords() {
    invoke_test_file("test_1.txt");
    TEST_ASSERT_EQUAL_INT(PARENS, token_type);
    TEST_ASSERT_EQUAL_STRING("()", token);

    invoke_test_file("test_2.txt");
    TEST_ASSERT_EQUAL_INT(INVALID, token_type);
    TEST_ASSERT_EQUAL_STRING("", token);

    invoke_test_file("test_3.txt");
    TEST_ASSERT_EQUAL_INT(BRACKETS, token_type);
    TEST_ASSERT_EQUAL_STRING("[1432]", token);

    invoke_test_file("test_4.txt");
    TEST_ASSERT_EQUAL_INT(NAME, token_type);
    TEST_ASSERT_EQUAL_STRING("abra123", token);

    invoke_test_file("test_5.txt");
    TEST_ASSERT_EQUAL_INT(PARENS, token_type);
    TEST_ASSERT_EQUAL_STRING("()", token);

    invoke_test_file("test_6.txt");
    TEST_ASSERT_EQUAL_INT(NAME, token_type);

    invoke_test_file("test_7.txt");
    TEST_ASSERT_EQUAL_INT(INVALID, token_type);

    invoke_test_file("test_8.txt");
    TEST_ASSERT_EQUAL_INT(')', token_type);
    TEST_ASSERT_EQUAL_STRING(")", token);

    invoke_test_file("test_9.txt");
    TEST_ASSERT_EQUAL_INT(CONST, token_type);
    TEST_ASSERT_EQUAL_STRING("const", token);

    invoke_test_file("test_10.txt");
    TEST_ASSERT_EQUAL_INT(PARENS, token_type);
    TEST_ASSERT_EQUAL_STRING("()", token);
}

void invoke_test_file(char *filename) {
    stdin_from_file(filename);
    get_token();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_count_keywords);
    return UNITY_END();
}