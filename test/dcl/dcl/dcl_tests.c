#include <stdio.h>
#include "unity.h"
#include "dcl/dcl.h"
#include "utils/io.h"

void restore_stdout(void) {
#ifdef _WIN32
    freopen("CON", "w", stdout);
#endif
#ifdef __unix__
    freopen("/dev/tty", "w", stdout);
#endif
}

void invoke_test_file(char *filename, char *expected);

void setUp() {

}

void tearDown() {

}

void test() {
    invoke_test_file("test_1.txt", "argv:  pointer to pointer to char");
    invoke_test_file("test_2.txt", "daytab:  pointer to array[13] of int");
    invoke_test_file("test_3.txt", "foo:  function(int, char) returning char");
    invoke_test_file("test_4.txt", "foo:  function() returning pointer to char");
    invoke_test_file("test_5.txt", "foo:  function( function(int, int) returning pointer to int) returning pointer to int");
    invoke_test_file("test_6.txt", "foo:  function(bar:  function() returning pointer to const int) returning pointer to const  int");
    invoke_test_file("test_7.txt", "foo:  function( function( function( pointer to int) returning pointer to int) returning pointer to int) returning pointer to int");
    invoke_test_file("test_8.txt", "c:  array[13] of int");
    invoke_test_file("test_9.txt", "x:  array[3] of pointer to function(y:  array[15] of int, z:  array[16] of array[17] of int) returning pointer to char");
    invoke_test_file("test_10.txt", "f:  function(x:  pointer to int) returning pointer to char");
}

void invoke_test_file(char *filename, char *expected) {
    freopen(filename, "r", stdin);
    freopen("ans.txt", "w", stdout);
    dcl_main();
    restore_stdout();
    freopen("ans.txt", "r", stdin);
    int exit_code;
    size_t chars_read;
    char *line = read_line_dyn(1000, 1000, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_STRING(expected, line);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}