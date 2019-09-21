#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_NUM

  /* TODO: Add more token types */

};

static int str_to_uint(char *args) {
    unsigned int sum = 0;
	while(*args != ' ')
	{
		sum = sum*10 + (*args-'0');
		args ++;
	}

	return sum;
}

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},     // spaces
  {"\\+", '+'},          // plus
  {"==", TK_EQ},         // equal
  {"\\-", '-'},          // minus
  {"\\*", '*' },         //multiply
  {"/", '/'},            //divide
  {"\\(", '('},          //left_bracket
  {"\\)", ')'},          //right_bracket
  {"[0-9]+",TK_NUM}        //number
};

#define ADD_TO_TOKENS tokens[nr_token].type = rules[i].token_type;  copy_char_array(rules[i].regex, tokens[nr_token].str)  
#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )
static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */

void copy_char_array(char a[],char b[]) {
    int i;
	for (i = 0; a[i] != '\0'; i ++) {
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

//static?
Token tokens[32] __attribute__((used)) = {}; //don't forget to add "static"
static int nr_token __attribute__((used))  = 0;

//static?
static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
			case TK_NOTYPE: { ADD_TO_TOKENS; nr_token++; break; } 
			case '+': { ADD_TO_TOKENS; nr_token++; break; }
			case TK_EQ: { ADD_TO_TOKENS; nr_token++; break;  } 
			case '-': { ADD_TO_TOKENS; nr_token++; break; }
			case '*': { ADD_TO_TOKENS; nr_token++; break; } 
			case '/': { ADD_TO_TOKENS; nr_token++; break; } 
			case '(': { ADD_TO_TOKENS; nr_token++; break; } 
			case ')': { ADD_TO_TOKENS; nr_token++; break; } 
            case TK_NUM: { char *str = &e[position-substr_len]; tokens[nr_token].type = str_to_uint(str); nr_token++; break; }
          default: TODO();
        }


        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
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

int return_end_index(char *args) {
    int i = 0;
   	char *ptr = args;
	while ( ptr[i] != '\0' ) {
	    i ++;
	}
	i --;
	return i;
}

uint32_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  return 0;
}


  /* TODO: Insert codes to evaluate the expression. */
//  TODO();
/*char *ptr_to_tokens_end = &tokens[0];
int p = 0;
int q = return_end_index(*ptr_to_tokens_end);

bool check_parentheses(int p, int q, Token *tokens[0]) {
    float weight = 0.0;
	if ( tokens[p]->type == '(' && tokens[q]->type == ')') {
		int left = p + 1;
		int right = q - 1;
		
		for ( left; left <= right; left ++ ) {
			
            if (weight < 0) {
			    return false;
			}

			else if (tokens[left]->type == '(') {
			    weight += 0.5;
			}

			else if (tokens[left]->type == ')') {
			    weight -= 0.5;
				
			}
	    }		

		if (weight > 0) {
		    return false;
		}
	
	}

	else {
	    return false;
	}
   
}*/

/*

uint32_t eval(int p, int q) {
    if ( p > q ) {
	    printf("Bad Expression!");
	}

	else if ( p == q ) {
	    return 
	}

	else if ( check_parentheses(p,q) == true ) {
        return eval(p+1, q-1);
	
	
	
	
	    return eval( p + 1, q - 1 );
	}

	else {
	    op = 
	    val1 = eval(p, op - 1);
		val2 = eval(op+1, q);

		switch () {
		    case '+': return val1 + val2;
		    case '-': return val1 - val2;
		    case '*': return val1 * val2;
            case '/': return val1 / val2;
		    default: assert(0);
		
		}
	}
}
*/
