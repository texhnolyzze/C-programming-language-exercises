

#include <unity.h>
#include <expr/op_parser.h>
#include <stdbool.h>
#include "expr/expr.h"
#include "utils/io/io.h"
#include "utils/test_utils/test_utils.h"

void setUp(void) {}

void tearDown(void) {}

void test_getop(void) {
    size_t start_offset = 0;
    size_t total_offset = 0;

    TEST_ASSERT_EQUAL_INT(NUMBER, getop("123", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(3, total_offset);

    TEST_ASSERT_EQUAL_INT(UNKNOWN_EXPR, getop("123.123.123", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(0, total_offset);

    TEST_ASSERT_EQUAL_INT(NUMBER, getop("123.123", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(7, total_offset);

    TEST_ASSERT_EQUAL_INT(NUMBER, getop(".123", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(4, total_offset);

    TEST_ASSERT_EQUAL_INT(NUMBER, getop("\t -.123", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(2, start_offset);
    TEST_ASSERT_EQUAL_size_t(7, total_offset);

    TEST_ASSERT_EQUAL_INT(NUMBER, getop("    +.321", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(4, start_offset);
    TEST_ASSERT_EQUAL_size_t(9, total_offset);

    char *line = "1 23";
    TEST_ASSERT_EQUAL_INT(NUMBER, getop(line, &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(1, total_offset);
    line += total_offset;
    TEST_ASSERT_EQUAL_INT(NUMBER, getop(line, &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(1, start_offset);
    TEST_ASSERT_EQUAL_size_t(3, total_offset);

    TEST_ASSERT_EQUAL_INT(NUMBER, getop("123", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(3, total_offset);

    TEST_ASSERT_EQUAL_INT(UNKNOWN_EXPR, getop("abracadabra", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(0, total_offset);

    TEST_ASSERT_EQUAL_INT(OPERATION, getop("\t+", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(1, start_offset);
    TEST_ASSERT_EQUAL_size_t(2, total_offset);

    TEST_ASSERT_EQUAL_INT(OPERATION, getop("   sin", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(3, start_offset);
    TEST_ASSERT_EQUAL_size_t(6, total_offset);

    TEST_ASSERT_EQUAL_INT(UNKNOWN_EXPR, getop("+-", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(0, total_offset);

    TEST_ASSERT_EQUAL_INT(END_OF_EXPR, getop("\0", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(0, start_offset);
    TEST_ASSERT_EQUAL_size_t(0, total_offset);

    TEST_ASSERT_EQUAL_INT(NUMBER, getop(" 2 +", &start_offset, &total_offset));
    TEST_ASSERT_EQUAL_size_t(1, start_offset);
    TEST_ASSERT_EQUAL_size_t(2, total_offset);
}

void test(const char *expr, double expected) {
    stdout_to_file("expr_tests_out.txt");
    struct stack *s = stack_create(100);
    evaluate_expr(expr, s);
    restore_stdout();
    stack_free(s, false);
    stdin_from_file("expr_tests_out.txt");
    int read_line_exit_code;
    size_t chars_read;
    char *line = read_line_dyn(100, 100, &read_line_exit_code, &chars_read);
    double actual = atof(line);
    TEST_ASSERT_EQUAL_FLOAT(expected, actual);
}

void test_evaluate_expr(void) {
    test("1 2 +", 3);
    test("1 2 -", -1);
    test("1 2 + 1 2 - +", 2);
    test("5 5 - ", 0);
    test("2 10 pow 1024 -", 0);
    test(" -3   2  pow     9  +  2   /   4    *   \n", 36);
    test("0", 0);
    test("-1 -1 *", 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_getop);
    RUN_TEST(test_evaluate_expr);
    return UNITY_END();
}