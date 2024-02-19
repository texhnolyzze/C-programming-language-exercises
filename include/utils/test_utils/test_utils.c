#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_utils.h"

void restore_stdout(void) {
#ifdef _WIN32
    freopen("CON", "w", stdout);
#endif
#ifdef __unix__
    freopen("/dev/tty", "w", stdout);
#endif
}

void stdin_from_file(const char *filename) {
    freopen(filename, "r", stdin);
}

void stdout_to_file(const char *filename) {
    freopen(filename, "w", stdout);
}

void setup_random() {
    time_t rawtime;
    time(&rawtime);
    srand(rawtime);
}

static int random_unseen_key(const struct random_test_key_value *data, size_t bound) {
    for (;;) {
        int key = rand();
        if (key == 0) {
            continue;
        }
        bool unseen = true;
        for (size_t i = 0; i < bound; i++) {
            if (data[i].key == key) {
                unseen = false;
                break;
            }
        }
        if (unseen) {
            return key;
        }
    }
}

struct random_test_key_value* create_random_test_key_values(size_t n) {
    struct random_test_key_value *data = malloc(n * sizeof(struct random_test_key_value));
    for (size_t i = 0; i < n; ++i) {
        data[i].key = random_unseen_key(data, i);
        data[i].value = rand();
    }
    return data;
}
