#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint64_t);

uint32_t isa_vaddr_read(vaddr_t addr, int len);

uint32_t vaddr_read(vaddr_t addr, int len);

static unsigned int str_to_uint(char *args);

//static int str_to_hex(char *args);

void isa_reg_display();

void isa_exec(vaddr_t *pc);

vaddr_t exec_once(void);

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args);

static int cmd_info(char *args);

static int cmd_x(char *args);

static int cmd_p(char *args);

static struct {
  char *name;
  char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Make the computer execuate N pieces of instructions, then stop. If N is omitted, use the default N=1", cmd_si },
  { "info", "Print the states of the registers and the information of watchpoints.", cmd_info },
  { "x", "scan the contents of the internal memory", cmd_x }, 
  { "p", "caculate the value of the expression", cmd_p },
  /* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

// The following function turns the string to unsigned int;
static unsigned int str_to_uint(char *args) {
	unsigned int sum = 0;
	while(*args != '\0')
	{
		sum = sum*10 + (*args-'0');
	    args ++;
	}

	return sum;
}

/*static unsigned int str_to_hex(char *args)：Actually, it turns the hexadecimal to decimal*/
static unsigned int str_to_hex(char *args) {
	unsigned int result = 0;
	args ++;
	args ++;
//Considering the condition that the address starts with "0x", it is necessary to shift the pointer 2 steps forward

	while(*args != '\0')
	{   
		if((*args >= '0') && (*args <= '9')) {
     		result = result*16+(*args-'0');
	    	args ++;
		}
// To change "A/a","B/b","C/c","D/d","E/e" and "F/f" to the integers them represents.
		else 
		{
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

static int cmd_si(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
 // int i;


  if (arg == NULL) {
	  /* no argument given */
	  cpu_exec(1);
  }

  else {
	  cpu_exec(str_to_uint(arg));
  }
  return 0;
}

static int cmd_info(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  
  if ( *arg == 'r' ) {
     isa_reg_display();
  }
  
  else if ( *arg == 'w' ) {
  }

  return 0;
}

static int cmd_x(char *args) {
   /* extract the first argument */
   char *arg = strtok(args," ");
   char *add = strtok(NULL," ");
   
   int i;
   int numbers = str_to_uint(arg);
   unsigned int addr = str_to_hex(add);
   for (i = 0; i < numbers; i ++) {
       printf(("0x%08x:      "),addr);
	   printf(("%-8u      "),isa_vaddr_read(addr, 1));//1 means 8 bits(1 byte),so 2 means 2 bytes, 3 means 3 bytes and so on.
	   printf(("0x%08x\n"),isa_vaddr_read(addr, 1 ));
       addr += 1;
   }
/*   printf("end\n");
   unsigned int addr  = str_to_hex(add);
   printf(("0x%08x:      "),addr);
   printf(("%u\n"),isa_vaddr_read(addr, 4));*/
   return 0;
}

/*
void show_array(Token *array) {
   int i;
   for ( i = 0; i < 3; i++,array++) {
       int j = 0;
	   while (array->str[j] != '\0') {
	       printf("%d",array->str[j]);
		   j++;
	   }
	   printf("\n");
   }
}
*/

static int cmd_p(char *args) {
//  Token *ptr = &tokens[0];
//	show_array(ptr);
//  make_token(args);
    char *arg = strtok(NULL,"$");
	bool success = true;
	int result = expr(arg,&success);
	if(success) {
	    printf("%x\n",result);
	}
	else {
	    printf("failed");
	}
    

	return 0;
/*	printf("Hi\n");
	return 1;   */
}

void ui_mainloop(int is_batch_mode) {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef HAS_IOE
    extern void sdl_clear_event_queue(void);
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}
