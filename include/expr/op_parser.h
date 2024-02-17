

#ifndef SANDBOX_OP_PARSER_H
#define SANDBOX_OP_PARSER_H

#define NUMBER 1
#define OPERATION 2
#define UNKNOWN_EXPR (-1)
#define END_OF_EXPR (-2)

int getop(const char *src, size_t *start_offset, size_t *total_offset);

#endif //SANDBOX_OP_PARSER_H
