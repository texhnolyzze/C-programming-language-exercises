#include <malloc.h>
#include "unity.h"
#include "dcl/dcl.h"
#include "utils/io/io.h"
#include "utils/test_utils/test_utils.h"

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
    invoke_test_file("test_11.txt", "pfa:  array[13] of pointer to function(x:  function(y:  function() returning pointer to char, z:  function() returning pointer to char) returning pointer to int) returning pointer to int");
}

void invoke_test_file(char *filename, char *expected) {
    stdin_from_file(filename);
    stdout_to_file("ans.txt");
    dcl_main();
    restore_stdout();
    stdin_from_file("ans.txt");
    int exit_code;
    size_t chars_read;
    char *line = read_line_dyn(1000, 1000, &exit_code, &chars_read);
    TEST_ASSERT_EQUAL_STRING(expected, line);
    free(line);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}