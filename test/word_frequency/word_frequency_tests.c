#include <unity.h>
#include "word_frequency/word_frequency.h"
#include "utils/test_utils/test_utils.h"

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
    ASSERT_ANS_FILE(ans_file, output_file)
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}