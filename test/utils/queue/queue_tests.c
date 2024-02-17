

#include <malloc.h>
#include <stdbool.h>
#include "unity.h"
#include "utils/queue/queue.h"

void setUp() {

}

void tearDown() {

}

void test() {
    struct queue *q = create_queue(5);

    TEST_ASSERT_EQUAL_INT(0, queue_size(q));

    queue_add(q, (void *) 54354);
    TEST_ASSERT_EQUAL_INT(1, queue_size(q));
    TEST_ASSERT_EQUAL_INT(54354, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(0, queue_size(q));

    queue_add(q, (void *) 1);
    queue_add(q, (void *) 2);
    queue_add(q, (void *) 3);
    queue_add(q, (void *) 4);
    queue_add(q, (void *) 5);
    TEST_ASSERT_EQUAL_INT(5, queue_size(q));
    TEST_ASSERT_EQUAL_INT(1, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(4, queue_size(q));

    queue_add(q, (void *) 6);
    TEST_ASSERT_EQUAL_INT(5, queue_size(q));
    TEST_ASSERT_EQUAL_INT(2, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(3, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(4, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(2, queue_size(q));

    queue_add(q, (void *) 7);
    TEST_ASSERT_EQUAL_INT(3, queue_size(q));

    queue_add(q, (void *) 8);
    TEST_ASSERT_EQUAL_INT(4, queue_size(q));

    queue_add(q, (void *) 9);
    TEST_ASSERT_EQUAL_INT(5, queue_size(q));
    TEST_ASSERT_EQUAL_INT(5, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(6, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(7, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(8, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(1, queue_size(q));
    TEST_ASSERT_EQUAL_INT(9, queue_remove(q));
    TEST_ASSERT_EQUAL_INT(0, queue_size(q));

    queue_add(q, (void *) -1);
    TEST_ASSERT_EQUAL_INT(1, queue_size(q));
    TEST_ASSERT_EQUAL_INT(-1, queue_remove(q));

    queue_add(q, 0);
    TEST_ASSERT_EQUAL_INT(1, queue_size(q));
    TEST_ASSERT_EQUAL_INT(0, queue_remove(q));

    queue_free(q, false);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}