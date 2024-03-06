#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "unity.h"
#include "utils/qsort/qsort.h"
#include "utils/test_utils/test_utils.h"

void setUp() {
    setup_random();
}

void tearDown() {

}

static int int_cmp(const int *l, const int *r) {
    if (*l < *r) {
        return -1;
    } else {
        return *l > *r ? 1 : 0;
    }
}

static int str_cmp(const char **str1, const char **str2) {
    return strcmp(*str1, *str2);
}

static void test_int() {
    size_t n = 10000;
    int arr[n];
    int expected_arr[n];
    for (int i = 0; i < n; ++i) {
        int r = rand();
        while (r == 0) {
            r = rand();
        }
        arr[i] = r;
    }
    memcpy(expected_arr, arr, sizeof(arr));
    qsort(expected_arr, n, sizeof(int), (int (*)(const void *, const void *)) int_cmp);
    myqsort(arr, n, sizeof(int), (const int (*)(const void *, const void *)) int_cmp);
    for (int i = 0; i < n; ++i) {
        TEST_ASSERT_EQUAL_INT(expected_arr[i], arr[i]);
    }
}

static void random_strings(size_t arr_len, char **strings) {
    for (size_t i = 0; i < arr_len; ++i) {
        int len = abs(rand()) % 10000;
        while (len == 0) {
            len = abs(rand());
        }
        char *str = malloc(len * sizeof(char));
        strings[i] = str;
        for (int j = 0; j < len - 1; ++j) {
            int c = 97 + rand() % 26;
            *str++ = (char) c;
        }
        *str = '\0';
    }
}

static void dup_strings(size_t n, char *const *src, char **dest) {
    for (size_t i = 0; i < n; ++i) {
        const char *str = src[i];
        char *dup = strdup(str);
        dest[i] = dup;
    }
}

static void test_str() {
    size_t arr_len = 1000;
    char *strings[arr_len];
    random_strings(arr_len, strings);
    char *expected_strings[arr_len];
    dup_strings(arr_len, strings, expected_strings);
    qsort(expected_strings, arr_len, sizeof(char *), (int (*)(const void *, const void *)) str_cmp);
    for (int i = 1; i < arr_len; ++i) {
        TEST_ASSERT_LESS_OR_EQUAL_INT(0, strcmp(expected_strings[i - 1], expected_strings[i]));
    }
    myqsort(strings, arr_len, sizeof(char *), (const int (*)(const void *, const void *)) str_cmp);
    for (int i = 0; i < arr_len; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_strings[i], strings[i]);
        free(expected_strings[i]);
        free(strings[i]);
    }
}

static void compare_with_stdlib(void) {
    size_t arr_len = 10000;
    for (int i = 0; i < 2; ++i) {
//      warm up
        char *strings[arr_len];
        random_strings(arr_len, strings);
        char *dup[arr_len];
        dup_strings(arr_len, strings, dup);
        qsort(strings, arr_len, sizeof(char *), (int (*)(const void *, const void *)) str_cmp);
        myqsort(dup, arr_len, sizeof(char *), (const int (*)(const void *, const void *)) str_cmp);
        for (int j = 0; j < arr_len; ++j) {
            free(strings[j]);
            free(dup[j]);
        }
    }
    double stdlib_ms_passed = 0.0;
    double my_ms_passed = 0.0;
    int n_tests = 100;
    for (int i = 0; i < n_tests; ++i) {
        char *strings[arr_len];
        random_strings(arr_len, strings);
        char *dup[arr_len];
        dup_strings(arr_len, strings, dup);
        clock_t start = clock();
        qsort(strings, arr_len, sizeof (char *), (int (*)(const void *, const void *)) str_cmp);
        clock_t end = clock();
        stdlib_ms_passed += (double) (end - start) / CLOCKS_PER_SEC * 1000.0F;
        start = clock();
        myqsort(dup, arr_len, sizeof(char *), (const int (*)(const void *, const void *)) str_cmp);
        end = clock();
        my_ms_passed += (double) (end - start) / CLOCKS_PER_SEC * 1000.0F;
        for (int j = 0; j < arr_len; ++j) {
            free(strings[j]);
            free(dup[j]);
        }
    }
    printf("stdlib: %f\n", stdlib_ms_passed / n_tests);
    printf("myqsort: %f\n", my_ms_passed / n_tests);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_int);
    RUN_TEST(test_str);
    RUN_TEST(compare_with_stdlib);
    return UNITY_END();
}