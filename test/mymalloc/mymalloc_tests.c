#include <time.h>
#include "unity.h"
#include "mymalloc/mymalloc.h"
#include "utils/test_utils/test_utils.h"

#define N 100000

void setUp() {
    setup_random();
}

void tearDown() {

}

int *nums[N];
int sz[N];

void test(void) {
    TEST_ASSERT_EQUAL_INT(0, total_allocated());
    TEST_ASSERT_EQUAL_INT(0, total_free_memory());
    long long expected_sum = 0;
    for (int i = 0; i < N; ++i) {
        int bytes = abs(rand()) % 512;
        int *arr = mymalloc(bytes);
        nums[i] = arr;
        sz[i] = bytes / sizeof(int);
        for (int j = 0; j < sz[i]; ++j) {
            arr[j] = rand();
            expected_sum += arr[j];
        }
    }
    long long actual_sum = 0;
    size_t allocated = total_allocated();
    for (int i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i) {
        int *arr = nums[i];
        for (int j = 0; j < sz[i]; ++j) {
            actual_sum += arr[j];
        }
        myfree(arr);
    }
    TEST_ASSERT_EQUAL_INT(expected_sum, actual_sum);
    size_t free_memory = total_free_memory();
    TEST_ASSERT_EQUAL_size_t(allocated, free_memory);
}

int main(void) {
    UNITY_BEGIN();
    clock_t start = clock();
    int n = 10;
    for (int i = 0; i < n; ++i) {
        RUN_TEST(test);
        osfree();
    }
    clock_t end = clock();
    double ms_passed = (double) (end - start) / CLOCKS_PER_SEC / n * 1000.0F;
    printf("%f\n", ms_passed);
    return UNITY_END();
}