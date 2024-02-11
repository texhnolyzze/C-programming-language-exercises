//
// Created by ikarimullin on 26.01.2024.
//

#include "unity.h"
#include "utils/strings.h"

void setUp() {

}

void tearDown() {

}

void test_mystrncat() {
    TEST_ASSERT_EQUAL_STRING("ababc", mystrncat(clone("abcde"), "abcdefg", 3));
    TEST_ASSERT_EQUAL_STRING("", mystrncat(clone(""), "abcdefg", 3));
    TEST_ASSERT_EQUAL_STRING("a", mystrncat(clone(" "), "abcdefg", 10));
    TEST_ASSERT_EQUAL_STRING("a", mystrncat(clone(" "), "ab", 10));
    TEST_ASSERT_EQUAL_STRING("abac", mystrncat(clone("boro"), "abactrgfa", 10));
    TEST_ASSERT_EQUAL_STRING("abac", mystrncat(clone("abac"), "", 10));
    TEST_ASSERT_EQUAL_STRING("ab", mystrncat(clone("  "), "ab", 10));
    TEST_ASSERT_EQUAL_STRING("  ", mystrncat(clone("  "), "", -10));
    TEST_ASSERT_EQUAL_STRING("cd", mystrncat(clone("cd"), "ab", 0));
}

void test_mystrncmp() {
    TEST_ASSERT_TRUE(mystrncmp("cara", "cadabra", 2) == 0);
    TEST_ASSERT_TRUE(mystrncmp("cara", "cadabra", 3) > 0);
    TEST_ASSERT_TRUE(mystrncmp("cara", "aadabra", 3) > 0);
    TEST_ASSERT_TRUE(mystrncmp("cara", "aadabra", 1) > 0);
    TEST_ASSERT_TRUE(mystrncmp("cara", "aadabra", 0) == 0);
    TEST_ASSERT_TRUE(mystrncmp("cara", "", 16) > 0);
    TEST_ASSERT_TRUE(mystrncmp("", "abra", 16) < 0);
}

void test_mystrncpy() {
    TEST_ASSERT_EQUAL_STRING("ab  ", mystrncpy(clone("    "), "abracadabra", 2));
    TEST_ASSERT_EQUAL_STRING("", mystrncpy(clone(""), "abracadabra", 2));
    TEST_ASSERT_EQUAL_STRING("a", mystrncpy(clone(" "), "abracadabr", 2));
    TEST_ASSERT_EQUAL_STRING("abran", mystrncpy(clone("baran"), "abdjgkf", 2));
    TEST_ASSERT_EQUAL_STRING("abra", mystrncpy(clone("abra"), "", 10));
}

void test_strend() {
    TEST_ASSERT_TRUE(strend("123456", "456"));
    TEST_ASSERT_TRUE(strend("123", ""));
    TEST_ASSERT_TRUE(strend("321", "1"));
    TEST_ASSERT_FALSE(strend("1", "321"));
}

void test_mystrcat() {
    TEST_ASSERT_EQUAL_STRING("123321", mystrcat(clone("123456"), "321"));
    TEST_ASSERT_EQUAL_STRING("abraca", mystrcat(clone("abraca"), "abraca"));
    TEST_ASSERT_EQUAL_STRING("abraca", mystrcat(clone("      "), "abraca"));
    TEST_ASSERT_EQUAL_STRING("123", mystrcat(clone("123"), ""));
}

void test_clone() {
    TEST_ASSERT_EQUAL_STRING("abracadabra", clone("abracadabra"));
    char *ptr = "abracadabra";
    TEST_ASSERT_FALSE(ptr == clone(ptr));
    TEST_ASSERT_EQUAL_STRING("", clone(""));
}

void test_reverse() {
    TEST_ASSERT_EQUAL_STRING("arba", reverse(clone("abra")));
    TEST_ASSERT_EQUAL_STRING("123", reverse(clone("321")));
    TEST_ASSERT_EQUAL_STRING("", reverse(clone("")));
    TEST_ASSERT_EQUAL_STRING("1", reverse(clone("1")));
}

void test_mystrcmp(void) {
    TEST_ASSERT_EQUAL_INT(0, mystrcmp("123", "123", false, true));
    TEST_ASSERT_LESS_OR_EQUAL(-1, mystrcmp("123", "3", false, true));
    TEST_ASSERT_GREATER_OR_EQUAL(1, mystrcmp("123", "3", true, true));
    TEST_ASSERT_EQUAL_INT(0, mystrcmp("abc", "ABC", false, false));
    TEST_ASSERT_LESS_OR_EQUAL(-1, mystrcmp("abc", "ABCa", false, false));
    TEST_ASSERT_GREATER_OR_EQUAL(1, mystrcmp("abc", "ABCa", true, false));
    TEST_ASSERT_LESS_OR_EQUAL(-1, mystrcmp("bacaa", "BaCaC", false, false));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_clone);
    RUN_TEST(test_strend);
    RUN_TEST(test_reverse);
    RUN_TEST(test_mystrcat);
    RUN_TEST(test_mystrncpy);
    RUN_TEST(test_mystrncmp);
    RUN_TEST(test_mystrncat);
    RUN_TEST(test_mystrcmp);
    return UNITY_END();
}