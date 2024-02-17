#include <unity.h>
#include "tail/tail.h"
#include "utils/io/io.h"
#include "utils/test_utils/test_utils.h"

static int exit_code;
static size_t chars_read;

void setUp(void) {
    const char *argv[1] = {"-5"};
    tail_init(1, argv);
}

void tearDown(void) {}

void test1(void) {
    stdin_from_file("test1.txt");
    stdout_to_file("test1-out.txt");
    tail();

    restore_stdout();
    stdin_from_file("test1-out.txt");
    TEST_ASSERT_EQUAL_STRING("7456754674567456", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("7456745674567262456453", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("6456456356", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("345634563456", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("3456", read_line_dyn(100, 100, &exit_code, &chars_read));
}

void test_big(void) {
    stdin_from_file("big.txt");
    stdout_to_file("test-big-out.txt");
    tail();

    restore_stdout();
    stdin_from_file("test-big-out.txt");
    TEST_ASSERT_EQUAL_STRING("    if ord(c) > 127 and c not in s:", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("        print i, c, ord(c), big[max(0, i-10):min(N, i+10)]", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("        s.add(c)", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("  print s", read_line_dyn(100, 100, &exit_code, &chars_read));
    TEST_ASSERT_EQUAL_STRING("  print [ord(c) for c in s]", read_line_dyn(100, 100, &exit_code, &chars_read));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test1);
    RUN_TEST(test_big);
    return UNITY_END();
}