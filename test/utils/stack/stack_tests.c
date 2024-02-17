

#include "unity.h"
#include "utils/stack/stack.h"

void setUp() {

}

void tearDown() {

}

void test() {
    struct stack *s = stack_create(10);
    TEST_ASSERT_EQUAL_INT(0, stack_size(s));
    double d1 = 1.0;
    stack_push(s, &d1);
    TEST_ASSERT_EQUAL_FLOAT(1.0, *((double *) stack_peek(s)));
    TEST_ASSERT_EQUAL_INT(1, stack_size(s));
    TEST_ASSERT_EQUAL_FLOAT(1.0, *((double *) stack_pop(s)));
    TEST_ASSERT_EQUAL_INT(0, stack_size(s));
    stack_push(s, &d1);
    stack_push(s, &d1);
    stack_push(s, &d1);
    double d2 = 2.0;
    TEST_ASSERT_EQUAL_FLOAT(1.0, *((double *) stack_pop(s)));
    stack_push(s, &d2);
    TEST_ASSERT_EQUAL_FLOAT(2.0, *((double *) stack_peek(s)));
    double d3 = 3.0;
    stack_push(s, &d3);
    TEST_ASSERT_EQUAL_INT(4, stack_size(s));
    stack_clear(s, false);
    TEST_ASSERT_EQUAL_INT(0, stack_size(s));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test);
    return UNITY_END();
}