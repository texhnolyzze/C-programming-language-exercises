#include <stdlib.h>
#include <time.h>
#include "unity.h"
#include "utils/list/list.h"

size_t sum_up(struct list *l);

void setUp() {
    time_t t;
    time(&t);
    srand(t);
}

void tearDown() {

}

void test() {
    struct list *l = list_create();
    TEST_ASSERT_EQUAL_INT(0, l->size);
    list_add(l, (void *) 1);
    list_add(l, (void *) 2);
    list_add(l, (void *) 3);
    TEST_ASSERT_EQUAL_INT(3, l->size);
    size_t sum = sum_up(l);
    TEST_ASSERT_EQUAL_INT(6, sum);
    list_free(l, false);
}

size_t sum_up(struct list *l) {
    struct list_node *current = l->head;
    size_t sum = 0;
    while (current != NULL) {
        sum += (size_t) current->data;
        current = current->next;
    }
    return sum;
}

void random_test() {
    int data[10000];
    size_t expected_sum = 0;
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        data[i] = rand();
        expected_sum += data[i];
    }
    struct list *l = list_create();
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        list_add(l, (void *) data[i]);
    }
    size_t sum = sum_up(l);
    TEST_ASSERT_EQUAL_size_t(expected_sum, sum);
    list_free(l, false);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    RUN_TEST(random_test);
    return UNITY_END();
}