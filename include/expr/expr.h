

#ifndef SANDBOX_CALCULATOR_H
#define SANDBOX_CALCULATOR_H

#include "utils/stack/stack.h"

extern const char POSSIBLE_OPERATIONS[8][4];

void expr(void);

void evaluate_expr(const char *line, struct stack *s);

#endif //SANDBOX_CALCULATOR_H
