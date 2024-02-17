#ifndef SANDBOXTEST_TEST_UTILS_H
#define SANDBOXTEST_TEST_UTILS_H

void stdin_from_file(const char *filename);

void stdout_to_file(const char *filename);

void restore_stdout(void);

#endif //SANDBOXTEST_TEST_UTILS_H
