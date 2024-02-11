//
// Created by ikarimullin on 24.01.2024.
//

#include <unity.h>
#include "utils/io.h"
#include "sort.h"
#include "malloc.h"

void setUp(void) {}

void tearDown(void) {}

void restore_stdout(void) {
#ifdef _WIN32
    freopen("CON", "w", stdout);
#endif
#ifdef __unix__
    freopen("/dev/tty", "w", stdout);
#endif
}

#define test(input_file, output_file, answer_file, numeric, reverse, case_insensitive) \
    freopen(input_file, "r", stdin); \
    freopen(output_file, "w", stdout); \
    char **argv = malloc(3 * sizeof (char *));                                                                              \
    int argc = 0;                                                                          \
    if (reverse) {                                                            \
        argv[argc++] = "-r";\
    }                                                                         \
    if (case_insensitive) {                                                   \
        argv[argc++] = "-f";                                                                               \
    }                                                                                  \
    if (numeric) {                                                                     \
        argv[argc++] = "-n";                                                                               \
    }                                                                                  \
    sort_init(argc, argv);\
    sort(); \
    restore_stdout(); \
     \
    int read_lines_exit_code; \
    size_t expected_lines_read; \
    freopen(answer_file, "r", stdin); \
    char **expected_lines = read_lines_dyn(100, 100, 100, &read_lines_exit_code, &expected_lines_read); \
    \
    size_t actual_lines_read; \
    freopen(output_file, "r", stdin); \
    char **actual_lines = read_lines_dyn(100, 100, 100, &read_lines_exit_code, &actual_lines_read); \
    TEST_ASSERT_EQUAL_size_t(expected_lines_read, actual_lines_read); \
    \
    for (size_t i = 0; i < expected_lines_read; ++i) { \
        TEST_ASSERT_EQUAL_STRING(*expected_lines++, *actual_lines++); \
    }


void test_1(void) {
    test("sort_test_1.txt", "sort_test_1_out.txt", "sort_test_1_ans.txt", false, false, false)
}

void test_2(void) {
    test("sort_test_2.txt", "sort_test_2_out.txt", "sort_test_2_ans.txt", false, true, false)
}

void test_3(void) {
    test("sort_test_3.txt", "sort_test_3_out.txt", "sort_test_3_ans.txt", true, false, false)
}

void test_4(void) {
    test("sort_test_4.txt", "sort_test_4_out.txt", "sort_test_4_ans.txt", false, false, true)
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);
    return UNITY_END();
}