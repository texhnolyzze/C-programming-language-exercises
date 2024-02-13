#include "unity.h"
#include "dcl/dcl_tokenizer.h"

void invoke_test_file(char *filename);

void setUp() {

}

void tearDown() {

}

void test_get_token() {
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
    TEST_ASSERT_EQUAL_INT('(', token_type);
    TEST_ASSERT_EQUAL_STRING("(", token);

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
}

void invoke_test_file(char *filename) {
    freopen(filename, "r", stdin);
    get_token();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_token);
    return UNITY_END();
}