/* abracadbra */
//
// Created by ikarimullin on 11.01.2024.
//

#include <stdio.h>
#include <stdbool.h>
#include "c_comment_remover.h"

void remove_comments(void) {
    int currentChar;
    int prevChar = '\0';
    bool insideString = false;
    bool insideSingleLineComment = false;
    bool insideMultilineComment = false;
    while ((currentChar = getchar()) != EOF) {
        if (insideString) {
            if (currentChar == '"' && prevChar != '\\') {
                insideString = false;
                prevChar = '\0';
            }
        } else if (insideSingleLineComment) {
            if (currentChar == '\n') {
                insideSingleLineComment = false;
                prevChar = '\0';
                currentChar = '\0';
                putchar('\n');
            }
        } else if (insideMultilineComment) {
            if (currentChar == '/' && prevChar == '*') {
                insideMultilineComment = false;
                prevChar = '\0';
                currentChar = '\0';
            }
        } else {
            if (currentChar == '"') {
                insideString = true;
            } else if (currentChar == '*' && prevChar == '/') {
                insideMultilineComment = true;
            } else if (currentChar == '/' && prevChar == '/') {
                insideSingleLineComment = true;
            }
        }
        if (!insideSingleLineComment && !insideMultilineComment) {
            if (prevChar == '/') {
                putchar(prevChar);
            }
            if (currentChar != '/' && currentChar != '\0') {
                putchar(currentChar);
            }
        }
        prevChar = currentChar;
    }
}
