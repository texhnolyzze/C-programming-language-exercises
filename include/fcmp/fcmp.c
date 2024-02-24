#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fcmp.h"
#include "string.h"

static const char *filename1;
static const char *filename2;
static int max_line = 5000;

static FILE *get_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Can't open %s in read mode", filename);
        exit(1);
    }
    return file;
}

int fcmp_init(int argc, const char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: fcmp filename1 filename2 [options]");
        return -1;
    }
    filename1 = *argv++;
    filename2 = *argv++;
    argc -= 2;
    for (int i = 0; i < argc; i += 2) {
        const char *arg = *argv++;
        if (strcmp("-ml", arg) == 0) {
            const char *arg_val = *argv++;
            if (sscanf(arg_val, "%u", &max_line) != 1 || max_line == 0) {
                fprintf(stderr, "Invalid -ml option: %s\n", arg_val);
                return -1;
            }
        } else {
            fprintf(stderr, "Unknown option: %s", *argv);
        }
    }
    return 0;
}

void fcmp(void) {
    FILE *file1 = get_file(filename1);
    FILE *file2 = get_file(filename2);
    char *line1 = malloc((max_line + 2) * sizeof(char));
    char *line2 = malloc((max_line + 2) * sizeof(char));
    if (line1 == NULL || line2 == NULL) {
        fprintf(stderr, "fcmp: insufficient memory\n");
        exit(1);
    }
    size_t line_num = 0;
    bool file1_has_line = false;
    bool file2_has_line = false;
    while (
            (file1_has_line = fgets(line1, max_line + 2, file1) != NULL) |
            (file2_has_line = fgets(line2, max_line + 2, file2) != NULL)
    ) {
        line_num++;
        if (!file1_has_line || !file2_has_line || strcmp(line1, line2) != 0) {
            printf("%zu", line_num);
            break;
        }
    }
    free(line1);
    free(line2);
    fclose(file1);
    fclose(file2);
}