//
// Created by ikarimullin on 26.01.2024.
//

#include "unity.h"
#include <malloc.h>
#include "utils/io.h"

#define LINE_LEN 10
char line[LINE_LEN + 1];

void setUp() {

}

void tearDown() {

}

void test_mystrncat() {
    freopen("EOF.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(-1, read_line(line, LINE_LEN));

    freopen("1-line.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(5, read_line(line, LINE_LEN));
    TEST_ASSERT_EQUAL_INT(-1, read_line(line, LINE_LEN));

    freopen("1-line-with-line-break.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(5, read_line(line, LINE_LEN));
    TEST_ASSERT_EQUAL_INT(-1, read_line(line, LINE_LEN));

    freopen("line-limit-exceeded.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(LINE_LEN, read_line(line, LINE_LEN));
    line[LINE_LEN] = '\0';
    TEST_ASSERT_EQUAL_STRING("1234567890", line);
    TEST_ASSERT_EQUAL_INT(6, read_line(line, LINE_LEN));
    line[6] = '\0';
    TEST_ASSERT_EQUAL_STRING("abcdef", line);

    freopen("line-break.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(0, read_line(line, LINE_LEN));
}

void test_read_lines() {
    int max_lines = 50;
    char **lines = malloc(max_lines * sizeof(char *));
    for (int i = 0; i < max_lines; ++i) {
        lines[i] = malloc((LINE_LEN + 1) * sizeof(char));
    }

    freopen("1-line.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(1, read_lines(lines, max_lines, LINE_LEN));
    TEST_ASSERT_EQUAL_STRING("12345", *lines);

    freopen("EOF.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(0, read_lines(lines, max_lines, LINE_LEN));

    freopen("2-lines-with-line-break.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(2, read_lines(lines, max_lines, LINE_LEN));
    TEST_ASSERT_EQUAL_STRING("123", *lines);
    TEST_ASSERT_EQUAL_STRING("321", *(lines + 1));

    freopen("line-break.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(1, read_lines(lines, max_lines, LINE_LEN));
    TEST_ASSERT_EQUAL_STRING("", *lines);

    freopen("line-limit-exceeded.txt", "r", stdin);
    TEST_ASSERT_EQUAL_INT(2, read_lines(lines, max_lines, LINE_LEN));
    TEST_ASSERT_EQUAL_STRING("1234567890", *lines);
    TEST_ASSERT_EQUAL_STRING("abcdef", *(lines + 1));

    free(lines);
}

void test_read_line_dyn() {
    int exit_code;
    size_t chars_read;
    char *str;

    freopen("EOF.txt", "r", stdin);
    str = read_line_dyn(0, 0, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_INT(0, exit_code);
    TEST_ASSERT_EQUAL_INT(0, chars_read);
    TEST_ASSERT_EQUAL_STRING("", str);

    str = read_line_dyn(LINE_LEN, 10, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_INT(-1, exit_code);
    TEST_ASSERT_EQUAL_INT(0, chars_read);
    TEST_ASSERT_EQUAL_STRING("", str);

    freopen("1-line.txt", "r", stdin);
    str = read_line_dyn(LINE_LEN, 1, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_INT(-1, exit_code);
    TEST_ASSERT_EQUAL_INT(5, chars_read);
    TEST_ASSERT_EQUAL_STRING("12345", str);

    freopen("2-lines-with-line-break.txt", "r", stdin);
    str = read_line_dyn(LINE_LEN, 1, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_INT(0, exit_code);
    TEST_ASSERT_EQUAL_INT(3, chars_read);
    TEST_ASSERT_EQUAL_STRING("123", str);
    str = read_line_dyn(LINE_LEN, 1, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_INT(0, exit_code);
    TEST_ASSERT_EQUAL_INT(3, chars_read);
    TEST_ASSERT_EQUAL_STRING("321", str);
    str = read_line_dyn(LINE_LEN, 1, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_INT(-1, exit_code);
    TEST_ASSERT_EQUAL_INT(0, chars_read);
    TEST_ASSERT_EQUAL_STRING("", str);

    freopen("line-limit-exceeded.txt", "r", stdin);
    str = read_line_dyn(LINE_LEN, 1, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_INT(0, exit_code);
    TEST_ASSERT_EQUAL_INT(LINE_LEN, chars_read);
    TEST_ASSERT_EQUAL_STRING("1234567890", str);
    str = read_line_dyn(LINE_LEN, 0, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_INT(-1, exit_code);
    TEST_ASSERT_EQUAL_INT(6, chars_read);
    TEST_ASSERT_EQUAL_STRING("abcdef", str);
}

void test_read_lines_dyn(void) {
    int exit_code;
    size_t lines_read;
    char **lines;

    freopen("EOF.txt", "r", stdin);
    read_lines_dyn(100, 100, 100, &exit_code, &lines_read);
    TEST_ASSERT_EQUAL_size_t(0, lines_read);
    TEST_ASSERT_EQUAL_size_t(-1, exit_code);

    freopen("1-line.txt", "r", stdin);
    lines = read_lines_dyn(100, 100, 100, &exit_code, &lines_read);
    TEST_ASSERT_EQUAL_size_t(1, lines_read);
    TEST_ASSERT_EQUAL_size_t(-1, exit_code);
    TEST_ASSERT_EQUAL_STRING("12345", lines[0]);

    freopen("1-line-with-line-break.txt", "r", stdin);
    lines = read_lines_dyn(100, 100, 100, &exit_code, &lines_read);
    TEST_ASSERT_EQUAL_size_t(1, lines_read);
    TEST_ASSERT_EQUAL_size_t(-1, exit_code);
    TEST_ASSERT_EQUAL_STRING("12345", lines[0]);

    freopen("2-lines-with-line-break.txt", "r", stdin);
    lines = read_lines_dyn(100, 100, 100, &exit_code, &lines_read);
    TEST_ASSERT_EQUAL_size_t(2, lines_read);
    TEST_ASSERT_EQUAL_size_t(-1, exit_code);
    TEST_ASSERT_EQUAL_STRING("123", lines[0]);
    TEST_ASSERT_EQUAL_STRING("321", lines[1]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_mystrncat);
    RUN_TEST(test_read_lines);
    RUN_TEST(test_read_line_dyn);
    RUN_TEST(test_read_lines_dyn);
    return UNITY_END();
}