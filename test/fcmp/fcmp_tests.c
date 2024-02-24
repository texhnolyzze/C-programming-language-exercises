#include <unity.h>
#include "utils/test_utils/test_utils.h"
#include "fcmp/fcmp.h"

#define ML 100
#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

void test_file(int test_num);

void setUp(void) {
    setup_random();
}

void tearDown(void) {}

void test(void) {

    for (int i = 0; i < N_TESTS; ++i) {
        test_file(i + 1);
    }
}

void test_file(int test_num) {
    char file1[100];
    sprintf(file1, "test-%d.a.txt", test_num);
    char file2[100];
    sprintf(file2, "test-%d.b.txt", test_num);
    const char *argv[4] = {file1, file2, "-ml", STRINGIFY(ML)};
    char output_file[100];
    sprintf(output_file, "test-%d.out.txt", test_num);
    char ans_file[100];
    sprintf(ans_file, "test-%d.ans.txt", test_num);
    stdout_to_file(output_file);
    TEST_ASSERT_EQUAL_INT(0, fcmp_init(4, argv));
    fcmp();
    restore_stdout();
    ASSERT_ANS_FILE(ans_file, output_file)
}

void random_test(void) {
    size_t n = 100;
    char *file1 = "random-test.a.txt";
    stdout_to_file(file1);
    int c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < ML; ++j) {
            while ((c = rand() % 127) <= 32);
            putchar(c);
        }
        putchar('\n');
    }
    restore_stdout();
    char *file2 = "random-test.b.txt";
    char *cmd[100];
#ifdef _WIN32
    sprintf(cmd, "copy %s %s", file1, file2);
#elif defined(__unix__)
    sprintf(cmd, "cp %s %s", file1, file2);
#else
    #error Unsupported OS
#endif
    TEST_ASSERT_EQUAL_INT(0, system(cmd));
    const char *out_file = "random-test.out.txt";
    stdout_to_file(out_file);
    const char *argv[4] = {file1, file2, "-ml", STRINGIFY(ML)};
    TEST_ASSERT_EQUAL_INT(0, fcmp_init(4, argv));
    fcmp();
    restore_stdout();
    stdin_from_file(out_file);
    char line[100];
    fgets(line, 100, stdin);
    TEST_ASSERT_EQUAL_STRING("", line);
    freopen(file1, "a", stdout);
    putchar('a');
    stdout_to_file(out_file);
    fcmp();
    restore_stdout();
    stdin_from_file(out_file);
    fgets(line, 100, stdin);
    TEST_ASSERT_EQUAL_STRING("101", line);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    RUN_TEST(random_test);
    return UNITY_END();
}