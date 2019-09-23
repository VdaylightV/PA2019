#ifndef __EXPR_H__
#define __EXPR_H__

#include "common.h"


typedef struct token {
    int type;
	char str[32];
} Token;


uint32_t expr(char *, bool *);

extern Token tokens[32];

char *find_end(char *args);

uint32_t check_parentheses(uint32_t p, uint32_t q, Token *token);

uint32_t find_op(uint32_t p, uint32_t q, Token *token);

uint32_t eval(uint32_t p, uint32_t q, Token *token);

#endif
