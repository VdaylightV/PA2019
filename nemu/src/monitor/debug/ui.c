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

static int str_to_int(char *args);

static int str_to_hex(char *args);

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

static int str_to_int(char *args) {
	int sum = 0;
	while(*args != '\0')
	{
		sum = sum*10 + (*args-'0');
	    args ++;
	}

	return sum;
}

static int str_to_hex(char *args) {
    int bit_count = 0;
	int result = 0;
	args ++;
	args ++;

	while(*args != '\0')
	{   
		result = result*10+(*args-'0');
		bit_count ++;
		args ++;
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
	  cpu_exec(str_to_int(arg));
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
   int numbers = str_to_int(arg);
   for (i = 0; i < numbers; i ++)
	   printf("Hi! ");
   int bit_count = str_to_hex(add);
   isa_vaddr_read(pmem[bit_count], 4);
   return 0;
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
