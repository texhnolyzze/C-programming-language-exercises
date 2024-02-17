#include <unity.h>
#include <malloc.h>
#include "cross_referencer/cross_referencer.h"
#include "utils/test_utils/test_utils.h"
#include "utils/io/io.h"

void setUp(void) {}

void tearDown(void) {}

void test1(void) {
    stdin_from_file("test-1.txt");
    cross_reference();
    TEST_PASS(); // no segfaults
}

void test2(void) {
    stdin_from_file("test-2.txt");
    char *out_file = "test-2.out.txt";
    stdout_to_file(out_file);
    cross_reference();
    restore_stdout();
    stdin_from_file(out_file);
    char **lines = malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; ++i) {
        lines[i] = malloc(101 * sizeof(char));
    }
    int lines_read = read_lines(lines, 100, 100);
    stdin_from_file("test-2.ans.txt");
    char **actual_line = lines;
    int exit_code = 0;
    size_t chars_read;
    while (exit_code != -1) {
        char *expected_line = read_line_dyn(100, 100, &exit_code, &chars_read);
        TEST_ASSERT_EQUAL_STRING(expected_line, *actual_line++);
    }
    if (actual_line - lines != lines_read) {
        TEST_FAIL();
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test1);
    RUN_TEST(test2);
    return UNITY_END();
}