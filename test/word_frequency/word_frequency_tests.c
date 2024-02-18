#include <unity.h>
#include <malloc.h>
#include "word_frequency/word_frequency.h"
#include "utils/test_utils/test_utils.h"
#include "utils/io/io.h"

void assert_ans(const char *ans_file, const char *out_file);

void test_file(int test_num);

void setUp(void) {
}

void tearDown(void) {}

void test(void) {
    for (int i = 0; i < N_TESTS; ++i) {
        test_file(i + 1);
    }
}

void test_file(int test_num) {
    char input_file[100];
    sprintf(input_file, "test-%d.txt", test_num);
    char output_file[100];
    sprintf(output_file, "test-%d.out.txt", test_num);
    char ans_file[100];
    sprintf(ans_file, "test-%d.ans.txt", test_num);
    stdin_from_file(input_file);
    stdout_to_file(output_file);
    word_frequency();
    restore_stdout();
    assert_ans(ans_file, output_file);
}

void assert_ans(const char *ans_file, const char *out_file) {
    stdin_from_file(ans_file);
    int exit_code;
    size_t expected_lines_read;
    char **expected_lines = read_lines_dyn(1000, 1000, 1000, &exit_code, &expected_lines_read);
    stdin_from_file(out_file);
    size_t actual_lines_read;
    char **actual_lines = read_lines_dyn(1000, 1000, 1000, &exit_code, &actual_lines_read);
    if (expected_lines_read != actual_lines_read) {
        TEST_FAIL();
    }
    for (int i = 0; i < actual_lines_read; ++i) {
        TEST_ASSERT_EQUAL_STRING(*expected_lines++, *actual_lines++);
    }
    expected_lines -= expected_lines_read;
    actual_lines -= actual_lines_read;
    for (int i = 0; i < expected_lines_read; ++i) {
        free(*expected_lines++);
        free(*actual_lines++);
    }
    free(expected_lines - expected_lines_read);
    free(actual_lines - expected_lines_read);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}