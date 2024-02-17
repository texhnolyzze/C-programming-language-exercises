

#ifndef SANDBOXTEST_DCL_TOKENIZER_H
#define SANDBOXTEST_DCL_TOKENIZER_H

#define DCL_MAX_TOKEN 100

enum {
    NAME,
    PARENS,
    BRACKETS,
    CONST,
    INVALID
};

extern int token_type;
extern char token[];

int get_token(void);

#endif //SANDBOXTEST_DCL_TOKENIZER_H
