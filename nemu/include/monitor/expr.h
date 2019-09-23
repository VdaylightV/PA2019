#ifndef __EXPR_H__
#define __EXPR_H__

#include "common.h"


typedef struct token {
    int type;
	char str[32];
} Token;


uint32_t expr(char *, bool *);

extern Token tokens[32];

#endif
