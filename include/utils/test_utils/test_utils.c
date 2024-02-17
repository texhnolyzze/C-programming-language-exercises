#include <stdio.h>
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
