#include <stdio.h>
#include <stdbool.h>
#include "clang_comment_remover.h"

void remove_comments(void) {
    int current_char;
    int prev_char = '\0';
    bool inside_string = false;
    bool inside_single_line_comment = false;
    bool inside_multiline_comment = false;
    while ((current_char = getchar()) != EOF) {
        if (inside_string) {
            if (current_char == '"' && prev_char != '\\') {
                inside_string = false;
                prev_char = '\0';
            }
        } else if (inside_single_line_comment) {
            if (current_char == '\n') {
                inside_single_line_comment = false;
                prev_char = '\0';
                current_char = '\0';
                putchar('\n');
            }
        } else if (inside_multiline_comment) {
            if (current_char == '/' && prev_char == '*') {
                inside_multiline_comment = false;
                prev_char = '\0';
                current_char = '\0';
            }
        } else {
            if (current_char == '"') {
                inside_string = true;
            } else if (current_char == '*' && prev_char == '/') {
                inside_multiline_comment = true;
            } else if (current_char == '/' && prev_char == '/') {
                inside_single_line_comment = true;
            }
        }
        if (!inside_single_line_comment && !inside_multiline_comment) {
            if (prev_char == '/') {
                putchar(prev_char);
            }
            if (current_char != '/' && current_char != '\0') {
                putchar(current_char);
            }
        }
        prev_char = current_char;
    }
}
