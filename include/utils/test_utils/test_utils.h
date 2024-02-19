#ifndef SANDBOXTEST_TEST_UTILS_H
#define SANDBOXTEST_TEST_UTILS_H

struct random_test_key_value {
    int key;
    int value;
};

void setup_random();

void stdin_from_file(const char *filename);

void stdout_to_file(const char *filename);

void restore_stdout(void);

struct random_test_key_value * create_random_test_key_values(size_t n);

#endif //SANDBOXTEST_TEST_UTILS_H
