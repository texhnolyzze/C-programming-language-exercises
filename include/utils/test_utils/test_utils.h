#ifndef SANDBOXTEST_TEST_UTILS_H
#define SANDBOXTEST_TEST_UTILS_H

#include "utils/io/io.h"
#include <malloc.h>

#define ASSERT_ANS_FILE(ans_file, out_file) \
    stdin_from_file(ans_file); \
    int exit_code; \
    size_t expected_lines_read; \
    char **expected_lines = read_lines_dyn(1000, 1000, 1000, &exit_code, &expected_lines_read); \
    stdin_from_file(out_file); \
    size_t actual_lines_read; \
    char **actual_lines = read_lines_dyn(1000, 1000, 1000, &exit_code, &actual_lines_read); \
    if (expected_lines_read != actual_lines_read) { \
        TEST_FAIL(); \
    } \
    for (int i = 0; i < actual_lines_read; ++i) { \
        TEST_ASSERT_EQUAL_STRING(*expected_lines++, *actual_lines++); \
    } \
    expected_lines -= expected_lines_read; \
    actual_lines -= actual_lines_read; \
    for (int i = 0; i < expected_lines_read; ++i) { \
        free(*expected_lines++); \
        free(*actual_lines++); \
    } \
    free(expected_lines - expected_lines_read); \
    free(actual_lines - expected_lines_read); \


struct random_test_key_value {
    int key;
    int value;
};

void setup_random();

void stdin_from_file(const char *filename);

void stdout_to_file(const char *filename);

void restore_stdout(void);

struct random_test_key_value * create_random_test_key_values(size_t n);

#endif //SANDBOXTEST_TEST_UTILS_H
