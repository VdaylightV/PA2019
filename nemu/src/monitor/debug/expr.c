#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_NUM, TK_CHAR, TK_HEX, TK_REG, TK_UEQ, TK_AND, DEREF

  /* TODO: Add more token types */

};

uint32_t str_to_uint_expression(char *args) {
    uint32_t sum = 0;
	while(*args != '\0')
	{
		sum = sum*10 + (*args-'0');
		args ++;
	}

	return sum;
}

uint32_t isa_vaddr_read(vaddr_t addr, int len);

uint32_t hex_to_uint32_t(char *args) {
    uint32_t result = 0;
	while(*args != '\0') {
	    if((*args >= '0') && (*args <= '9')) {
		    result = result*16 + (*args-'0');
			args ++;
		}
		else {
			int condition = *args - '0';
			switch(condition) {
				case 17 : result = result*16+10;break;
				case -15: result = result*16+10;break; 
				case 18 : result = result*16+11;break;
				case -14: result = result*16+11;break;	 
				case 19 : result = result*16+12;break;
				case -13: result = result*16+12;break;	 
				case 20 : result = result*16+13;break;
				case -12: result = result*16+13;break;	 
				case 21 : result = result*16+14;break;
				case -11: result = result*16+14;break;	 
				case 22 : result = result*16+15;break;	 
				case -10: result = result*16+15;break;	 
	 		}
		    args ++; 
		}
	}
    return result;
}

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {"[\\$]{1}[e]{2,3}",TK_REG},        // register
  {" +", TK_NOTYPE},				 // spaces
  {"\\+", '+'},						 // plus
  {"==", TK_EQ},					 // equal
  {"!=", TK_UEQ},                                // unequal
  {"\\-", '-'},						 // minus
  {"\\*", '*' },					 // multiply
  {"/", '/'},						 // divide
  {"\\(", '('},						 // left_bracket
  {"\\)", ')'},						 // right_bracket
  {"^[0]{1}[x]{1}[0-9a-fA-F]+",TK_HEX},   // hex_number
  {"[0-9]+",TK_NUM},			     // number
  {"[u]{1}",TK_CHAR},			     // character
  {"&&", TK_AND},                    // and     
};
#define Token_length 500
#define ADD_TO_TOKENS tokens[nr_token].type = rules[i].token_type;  copy_char_array(substr_start, tokens[nr_token].str, substr_len)  
#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )
static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */

void copy_char_array(char *a, char b[], int substr_len) {
    int i;
	for (i = 0; i < substr_len; i ++) {
	    b[i] = a[i];
	}
    b[i] = '\0';
}

void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

typedef struct token_pro {
  int type;
  char str[32];
  int prefer;
} Token_pro;
//static?
static Token tokens[Token_length] __attribute__((used)) = {}; //don't forget to add "static"
//I choose to copy a copy of the tokens
static Token_pro tokens_copy[Token_length];
static int nr_token __attribute__((used))  = 0;
uint32_t token_end = 0;
//static?
static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  token_end = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s\n",
           i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
			case TK_NOTYPE: {/* ADD_TO_TOKENS; nr_token++; token_end ++;*/ break; } 
	        case TK_CHAR: {/* ADD_TO_TOKENS; nr_token++; token_end ++;*/ break; } 
			case '+': { ADD_TO_TOKENS; nr_token++; token_end ++; break; }
			case TK_EQ: { ADD_TO_TOKENS; nr_token++; token_end ++; break;  } 
			case '-': { ADD_TO_TOKENS; nr_token++; token_end ++; break; }
			case '*': { ADD_TO_TOKENS; nr_token++; token_end ++; break; } 
			case '/': { ADD_TO_TOKENS; nr_token++; token_end ++; break; } 
			case '(': { ADD_TO_TOKENS; nr_token++; token_end ++; break; } 
			case ')': { ADD_TO_TOKENS; nr_token++; token_end ++; break; }
	    	case TK_NUM: { ADD_TO_TOKENS; nr_token++; token_end ++; break; } 
			case TK_UEQ: { ADD_TO_TOKENS; nr_token++; token_end ++; break; } 
			case TK_AND: { ADD_TO_TOKENS; nr_token++; token_end ++; break; }
			case TK_HEX: { ADD_TO_TOKENS; nr_token++; token_end ++; break; }
//	    	case TK_REG: { ADD_TO_TOKENS; nr_token++; token_end ++; break; } 
        //    case TK_NUM: { char *str = &e[position-substr_len]; tokens[nr_token].type = str_to_uint(str); nr_token++; break; }
          default: assert(0);
        }


        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  for ( int i = 0; i < nr_token; i++ ) {
      if (tokens[i].type == '*' && (i == 0 || tokens[i-1].type == '(' || tokens[i-1].type == '+' || tokens[i-1].type == '-' || tokens[i-1].type == '*' || tokens[i-1].type == '/' || tokens[i-1].type == TK_AND || tokens[i-1].type == TK_UEQ)) {
	      tokens[i].type = DEREF;
	  }
  }

  for ( int i = 0; i < nr_token; i ++ ) {
      tokens_copy[i].type = tokens[i].type;
      int j = 0;
	  while ( tokens[i].str[j] != '\0' ) {
	      tokens_copy[i].str[j] = tokens[i].str[j];
		  j ++;
	  }
	  
	  while ( j <= 31 ) {
	      tokens_copy[i].str[j] = '\0';
		  j ++;
	  }
	  //To avoid the content left in the tokens will impact the nect strtok
	  switch ( tokens[i].type ) {
          case '+': case '-': { tokens_copy[i].prefer = 4; break; }
		  case '*': case '/': { tokens_copy[i].prefer = 3; break; }
		  case TK_EQ: case TK_UEQ: { tokens_copy[i].prefer = 7; break; }
		  case DEREF: { tokens_copy[i].prefer = 2; break; }
		  case TK_AND: { tokens_copy[i].prefer = 11; break; }
		  default: {tokens_copy[i].prefer = 0; break;}
          	  
	  }
  }

  return true;
}

char *find_end(char *args) {
    char *end = args;
	while ( *end != '\0') {
	    end ++;
	}
	end --;
	return end;
}

/*
uint32_t return_end_index(Token *args) {
    uint32_t i = 0;
   	Token *ptr = args;
	while ( ptr[i] != '\0' ) {
	    i ++;
	}
	i --;
	return i;
}
*/


//char *ptr_to_tokens_end = &tokens[0];
//uint32_t p = 0;
//uint32_t q = *(&nr_token); 

//there exist a cast from int to uinr32_t, because the nr_token was originally "int", now I turn it to "uint32_t";
//Don't forget that the "Token *token" was a pointer, whose type is "Token" and name is "token"!!!!!!!
uint32_t check_parentheses(uint32_t p, uint32_t q/*, Token *token*/) {
    float weight = 0.0;
	float weight_min = weight;
    uint32_t i = p;

	for ( ; i <= q; i ++ ) {
	    if ( tokens_copy[i].type == '(' ) {
		    weight += 0.5;
		}
	    
		else if ( tokens_copy[i].type == ')' ) {
		    weight -= 0.5; 
			if ( weight < weight_min ) {
			    weight_min = weight;
			}
		}
	}

	if ( weight != 0.0 ) {
	    return 3;
	}

	else if ( tokens_copy[p].type == '(' && tokens_copy[q].type == ')') {
		uint32_t left = p + 1;
		uint32_t right = q - 1;
		
		for ( ; left <= right; left ++ ) {
			
            if (weight < 0) {
			    return 0;
			}

			else if (tokens_copy[left].type == '(') {
			    weight += 0.5;
			}
//	    return 100;

			else if (tokens_copy[left].type == ')') {
			    weight -= 0.5;
				
			}
	    }
        return 1;		
	}
	
	return 2;
   
}
//According to the check_parentheses, if return 3,it means illegeal brackets, if return 0, it means no big brackets surrounding the whole expression but the beginning and end of the expression are brackets, then if it return 1, it means there is a big pair of brackets surrounding the expression, last if it return 2, it means there is no brackets surrounding the expression and the beginning and end of the expression are not brackets.

/*
uint32_t find bracket(uint32_t p, uin32_t q, Token *tokens) {
    uint32_t index = p;
}
*/
uint32_t find_op(uint32_t p, uint32_t q/*, Token *token*/) {
    uint32_t index = p;
    float weight = 0.0; 
	uint32_t max_prefer = 0;

	for ( int k = p; k <= q; k++ ) {
	    if ( tokens_copy[k].type == '(' ) {
		    weight += 0.5;
		}

		if ( tokens_copy[k].type == ')' ) {
			weight -= 0.5;
		}

		if ( weight == 0.0 && tokens_copy[k].prefer >= max_prefer ) {
		    max_prefer = tokens_copy[k].prefer;
			index = k;
		}
	}

	return index;

/*
	for ( int k = 0; k < nr_token; k ++ ) {
	    if ( tokens_copy[k].prefer > max_prefer ) {
		    max_prefer = tokens_copy[k].prefer;
		}
	
	}

	if ( max_prefer == 4  ) {

 //   while ( token[j].type != '*' && token[j].type != '/' && token[j].type != '-' && token[j].type != '+' ) { 
	
		float weight = 0.0;
	    if ( tokens[j].type == ')' ) {
			weight += 0.5;
			j --;
			while ( weight != 0.0 ) {
		        if ( tokens[j].type != ')' && tokens[j].type != '(' ) {
				    j --;
				}

			    else if ( tokens[j].type == ')' ) {
				    weight += 0.5;
					j --;
				}	

			    else if ( tokens[j].type == '(' ) {
				    weight -= 0.5;
					j --;
				}	
			    
	            		
//		    	while ( token[j].type == ')' ) {
//			        weight += 0.5;
//			     	j --;
//		    	}
//		        while ( token[j].type != '(' ) {
//			        j --;
//			    }
//
//		    	while ( token[j].type == '(' ) {
//			    	weight -= 0.5;
//			        j --;
//		    	}
 //               while ( weight != 0.0 ) {
//			        j --;
//			    	if ( token[j].type == '(' ) {
//				        weight -= 0.5;
//			    	}
//		    	}
//				
	    	}
    	}	
		else if ( tokens[j].type == TK_NUM ) {
		    j --;
		}
//	}	

		if ( tokens[j].type == '+' || tokens[j].type == '-' ) {
			return j;
		}

	//    while ( token[i].type != '*' && token[i].type != '/' && token[i].type != '-' && token[i].type != '+' ) {
			weight = 0.0;
			if ( tokens[i].type == '(' ) {
				weight += 0.5;
				i ++;
				while ( weight != 0 ) {
					if ( tokens[i].type != ')' && tokens[i].type != '(' ) {
						i ++;
					}

					else if ( tokens[i].type == '(' ) {
						weight += 0.5;
						i ++;
					}

					else if ( tokens[i].type == ')' ) {
						weight -= 0.5;
						i ++;
					}
				
				}

					
//				while ( token[i].type == '(' ) {
//					weight += 0.5;
//					i ++;
//				}
//				while ( token[i].type != ')' ) {
//					i ++;
//				}
//
//				while ( token[i].type == ')' ) {
//					i ++;	
//					weight -= 0.5;		
//				}
//				while ( weight != 0.0 ) {
//					i ++;
//					if ( token[i].type == ')' ) {
//						weight -= 0.5;
//					}
//				}
//				i ++;
//				
		 }
			else if ( tokens[i].type == TK_NUM ) {
				i ++;
				}
	//	}
				
		if ( i == j ) {
			return i;
		}

		if ( i > j ) {
			assert(0);
		} //So end with 0 or 1 means the fault was due to find_op function

		else if ( tokens[i].type == '+' || tokens[i].type == '-' ) {
			return find_op( i, j-1);
		}

		else if ( tokens[i].type == '*' || tokens[i].type == '/' ) {
			index = j;
			if ( find_op( i+1, j) == j  ) {
				return index;
			}
			else if ( find_op ( i+1, j) != i ) {
				return find_op ( i+1, j);
			}
		}

	}

	else if ( max_prefer > 4 ) {
	
	}
	
	assert(1);
	return -1;
*/
}


uint32_t eval(uint32_t p,uint32_t q/*, Token *token*/) {
    if ( p > q ) {
		return -1;
	}

	else if ( p == q ) {
		if ( tokens_copy[p].type == TK_NUM ) {
	        return str_to_uint_expression(&(tokens_copy[p].str[0]));
		}

		else if ( tokens_copy[p].type == TK_HEX ) {
		    return hex_to_uint32_t(&(tokens_copy[p].str[0]));
		}

		else {
		    assert(0); 
			return -1;
		}
	}

	else if ( check_parentheses( p, q/*, token*/ ) == 1 ) {
	    return eval( p + 1, q - 1/*, token*/ );
	}

	else {
	    uint32_t op = find_op( p, q/*, token*/ );
		if ( tokens_copy[op].type != DEREF ) {
			uint32_t val1 = eval( p, op - 1/*, token*/ );
			uint32_t val2 = eval( op + 1, q/*, token*/ );

			switch ( tokens_copy[op].type ) {
				case '+': return val1 + val2;
				case '-': return val1 - val2;
				case '*': return val1 * val2;
				case '/': { assert( val2 != 0 ); return val1 / val2; }
				case TK_EQ: { if ( val1 == val2 ) { return 1;} else { return 0; } break; }
				case TK_UEQ: { if ( val1 != val2 ) { return 1;} else { return 0; } break; }
				case TK_AND: return val1 && val2;
				default: assert(0); return -1; // So end with 2 means the fault was in eval function
			
			 }
		}

		else {
		    uint32_t val1 = eval( op + 1, q );
		    return isa_vaddr_read(val1, 1);	
		
		}
	 }
}


uint32_t expr(char *e, bool *success) {
  if (!make_token(e)) {
	*success = false;
  }

 assert(token_end!=0);

 uint32_t expression_value = eval( 0, token_end - 1 );
 uint32_t brackets = check_parentheses( 0, token_end - 1 );
 // return expression_value;

// The following codes are used to test the functions above!!!
  printf("Hi\n");

  Token_pro *ptr = &tokens_copy[0];
  printf("content:\n");
  for ( int i = 0; i < token_end; i ++ ) {
      int j = 0;
	  while ( ptr[i].str[j] != '\0' ) {
	      printf("%c", ptr[i].str[j]);
		  j ++;
	  }
  }
  printf("\nEnd Here!!\n");

  uint32_t op_index = find_op(0, token_end-1);



  printf("OP:%c, OP_INDEX:%u\n",tokens_copy[op_index].type, op_index);

  printf("VALUE:%u\n",expression_value);
  printf("BRACKETS:%u\n",brackets);

  return 0;
}
  /* TODO: Insert codes to evaluate the expression. */
//  TODO();
