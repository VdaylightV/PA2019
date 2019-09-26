#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

//static char buf[]

static char buf[65536] = {'\0'};
static uint32_t count = 0;

uint32_t pow_uint32_t(uint32_t base, int exponent) {
    uint32_t result = 1;
   	while ( exponent >= 1 ) {
        result *= base;
		exponent --;
	}
	return result;
}

//The length include '\0'
uint32_t length_judge(char str[]) {
    uint32_t count = 0;
	while ( str[count] != '\0' ) {
	    count ++;
	}
	return count+1;
}

uint32_t choose(uint32_t n) {
    int seed = time(0);
	srand(seed);
	uint32_t rand_num = (rand()%(n));
	return rand_num;
}

char *find_end( char *begin ) {
	while ( *begin != '\0' ) {
	    begin ++;
	}
	return begin;
}

uint32_t find_end_index( char *begin ) {
    uint32_t index = 0;
	while ( *begin != '\0' ) {
	    begin ++;
		index ++;
	}
	index --;
	return index;
}

uint32_t judge_bits( uint32_t number ) {
    uint32_t bit_count = 1;
	uint32_t division = 10;
	while ( number/division != 0 ) {
	    number = number / division;
		bit_count ++;
	}
	return bit_count;
}

void gen_num() {
    int seed = time(0);
	srand(seed);
	uint32_t rand_num = (rand()%(2500));
    
	uint32_t division = 10;
	uint32_t count = judge_bits( rand_num );

	char *begin = &buf[0];
	char *end = find_end(begin);

	uint32_t temp = rand_num;
	for ( ; count >= 1; count --, end ++ ) {
	    uint32_t bit = temp/pow_uint32_t( division, count - 1 );
		*end = '0' + bit;
		temp = (temp % pow_uint32_t( division, count - 1));
	}
	*end = 'u';
    end ++;
	*end = '\0';

}

void gen_rand_op() {
	int seed = time(0);
	srand(seed);
	uint32_t rand_num = (rand()%(4));

	char *begin = &buf[0];
	char *end = find_end(begin);

	switch(rand_num) {
	    case 0: { *end = '+'; end ++; *end = '\0'; break; }
		case 1: { *end = '-'; end ++; *end = '\0'; break; }
        case 2: { *end = '*'; end ++; *end = '\0'; break; }
        case 3: { *end = '/'; end ++; *end = '\0'; break; }
	}
}

void gen_space() {
    int seed = time(0);
	srand(seed);
	uint32_t rand_num = (rand()%(10));

	char *begin = &buf[0];
	char *end = find_end(begin);

	while ( rand_num != 0 ) {
	    *end = ' ';
		end ++;
		rand_num --;
	}
	*end = '\0';
}


void gen(char character) {
   char *begin = &buf[0];
   char *end = find_end(begin);
   
   assert(*end == '\0');
   *end = character;
   end ++;
   *end = '\0';
   assert(*end == '\0');
}


// this should be enough
static inline void gen_rand_expr() {
	count ++;
//	assert(count>3);
//	uint32_t rand = choose(3);
//    static uint32_t count_re = 0;
/*	if ( rand !=0 && rand !=1 ) {
	    count_re ++;
	}
	if ( count_re < 2 ) {
        while ( rand == 0 && rand == 1 ) {
		    rand = choose(3);
		}	      
	}
	if ( count_re >= 2 ) {
        while ( rand != 0 && rand != 1 ) {
		    rand = choose(3);
		}	      
	}
*/
    uint32_t rand = choose(3);
    if ( count >= 15  ) {
	    rand = 0;
	}
	sleep(1);
	switch (rand) {
	    case 0 : { gen_num(); break; }
		case 1 : { gen('('); gen_space(); gen_rand_expr();gen_space();  gen(')'); break; }
		default : { gen_rand_expr(); gen_space(); gen_rand_op(); gen_space(); gen_rand_expr(); break; }
	}
	assert(buf[0] != '\0');

/*
    switch  (rand) {
//      switch (day) {
	    case 0: { gen_num(); break; }
		case 1: { gen('('); gen_num(); gen_rand_op();sleep(1); gen(')'); break; }
		default: { gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break; }
	}
*/
}

static char code_buf[65536];
/*int i = 0;
while ( buf[i] != '\0' ) {
    code_buf[i] = buf[i];
	i ++;
}
code_buf[i] = '\0';
*/
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

int main(int argc, char *argv[]) {
/*  int m = 0;
  while ( buf[m] != '\0' ) {
      printf("%c\n",buf[m]);
	  m ++;
  }
*/

  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    buf[0] = '\0';  
	gen_rand_expr();
	count = 0;
	sleep(1);
    assert(buf[0] != '\0');
	if ( length_judge(buf) > 65536 ) {
	    break;
	}
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
