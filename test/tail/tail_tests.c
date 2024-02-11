//
// Created by ikarimullin on 02.02.2024.
//

#include <unity.h>
#include <tail.h>
#include "utils/io.h"

static int exit_code;
static size_t chars_read;

void restore_stdout();

void setUp(void) {
    const char *argv[1] = {"-5"};
    tail_init(1, argv);
}

void tearDown(void) {}

void test1(void) {
    freopen("test1.txt", "r", stdin);
    freopen("test1-out.txt", "w", stdout);
    tail();

    restore_stdout();
    freopen("test1-out.txt", "r", stdin);
    TEST_ASSERT_EQUAL_STRING("7456754674567456", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("7456745674567262456453", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("6456456356", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("345634563456", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("3456", read_line_dyn(100, 100, &exit_code, &chars_read));
}

void test_big(void) {
    freopen("big.txt", "r", stdin);
    freopen("test-big-out.txt", "w", stdout);
    tail();

    restore_stdout();
    freopen("test-big-out.txt", "r", stdin);
    TEST_ASSERT_EQUAL_STRING("    if ord(c) > 127 and c not in s:", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("        print i, c, ord(c), big[max(0, i-10):min(N, i+10)]", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("        s.add(c)", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("  print s", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("  print [ord(c) for c in s]", read_line_dyn(100, 100, &exit_code, &chars_read));
}

void restore_stdout() {
#ifdef _WIN32
    freopen("CON", "w", stdout);
#endif
#ifdef __unix__
    freopen("/dev/tty", "w", stdout);
#endif
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test1);
    RUN_TEST(test_big);
    return UNITY_END();
}