#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "dcl.h"

void dcl(bool function_argument, char *name, char *datatype, char *out);

void dirdcl(bool function_argument, char *name, char *datatype, char *out);

void dcl_top(
        bool function_argument,
        char **name_target,
        char **datatype_target,
        bool *has_const_target,
        char **out_target
);

void function_arguments(char *out);

void dcl_main(void) {
    char **name = malloc(sizeof(char *));
    char **datatype = malloc(sizeof(char *));
    bool *has_const = malloc(sizeof(bool *));
    char **out = malloc(sizeof(char *));
    while (get_token() != EOF) {
        if (token_type == '\n') {
            continue;
        }
        dcl_top(false, name, datatype, has_const, out);
        printf("%s: %s%s %s\n", *name, *out, *has_const ? " const " : "", *datatype);
        free(*name);
        free(*datatype);
        free(*out);
    }
    free(name);
    free(datatype);
    free(has_const);
    free(out);
}

void dcl_top(
        bool function_argument,
        char **name_target,
        char **datatype_target,
        bool *has_const_target,
        char **out_target
) {
    char *name = malloc((DCL_MAX_TOKEN + 1) * sizeof(char));
    char *datatype = malloc((DCL_MAX_TOKEN + 1) * sizeof(char));
    char *out = malloc(1000 * sizeof(char));
    *name = '\0';
    *datatype = '\0';
    *out = '\0';
    bool has_const = false;
    if (token_type == NAME) {
        strcpy(datatype, token);
    } else if (token_type == CONST) {
        has_const = true;
        get_token();
        if (token_type != NAME) {
            printf("Expected first token after CONST to be of type NAME, got %d: %s\n", token_type, token);
            return;
        } else {
            strcpy(datatype, token);
        }
    } else {
        printf("Expected first token to be of type NAME or CONST, got %d: %s\n", token_type, token);
        return;
    }
    dcl(function_argument, name, datatype, out);
    if (token_type != '\n' && token_type != EOF && token_type != ')' && token_type != ',') {
        printf("syntax error: %s\n", token);
    }
    *name_target = name;
    *datatype_target = datatype;
    *has_const_target = has_const;
    *out_target = out;
}

void dcl(bool function_argument, char *name, char *datatype, char *out) {
    get_token();
    if (function_argument && (token_type == ')' || token_type == ',')) {
        return;
    }
    int count_stars = 0;
    while (token_type == '*') {
        count_stars++;
        get_token();
    }
    if (!function_argument || (token_type != ')' && token_type != ',')) {
        dirdcl(function_argument, name, datatype, out);
    }
    while (count_stars-- > 0) {
        strcat(out, " pointer to");
    }
}

void dirdcl(bool function_argument, char *name, char *datatype, char *out) {
    if (token_type == '(') {
        if (function_argument) {
            function_arguments(out);
        } else {
            dcl(function_argument, name, datatype, out);
            if (token_type != ')') {
                printf("error: missing ')' at %s\n", token);
            }
        }
    } else if (token_type == NAME) {
        strcpy(name, token);
    } else {
        printf("error: expected NAME or (dcl) at %s\n", token);
    }
    get_token();
    if (token_type == '(') {
        function_arguments(out);
    } else {
        while (token_type == PARENS || token_type == BRACKETS) {
            if (token_type == PARENS) {
                strcat(out, " function() returning");
            } else {
                strcat(out, " array");
                strcat(out, token);
                strcat(out, " of");
            }
            get_token();
        }
    }
}

void function_arguments(char *out) {
    strcat(out, " function(");
    do {
        get_token();
        if (token_type == ')') {
            break;
        }
        char **name_target = malloc(sizeof(char *));
        char **datatype_target = malloc(sizeof(char *));
        bool *has_const_target = malloc(sizeof(bool *));
        char **out_target = malloc(sizeof(char *));
        dcl_top(true, name_target, datatype_target, has_const_target, out_target);
        if (strlen(*name_target) != 0) {
            strcat(out, *name_target);
            strcat(out, ": ");
        }
        if (strlen(*out_target) != 0) {
            strcat(out, *out_target);
            strcat(out, " ");
        }
        if (*has_const_target) {
            strcat(out, "const ");
        }
        strcat(out, *datatype_target);
        free(*name_target);
        free(*datatype_target);
        free(*out_target);
        free(name_target);
        free(datatype_target);
        free(out_target);
        free(has_const_target);
        if (token_type == ')') {
            break;
        } else if (token_type != ',') {
            printf("syntax error: %s", token);
            break;
        } else {
            strcat(out, ", ");
        }
    } while (true);
    strcat(out, ") returning");
}
