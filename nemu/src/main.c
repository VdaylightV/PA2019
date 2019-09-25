#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"
#include "assert.h"

int init_monitor(int, char *[]);
void ui_mainloop(int);
uint32_t expr(char *e, bool *success);  

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
  int is_batch_mode = init_monitor(argc, argv);

  /* Receive commands from user. */
  ui_mainloop(is_batch_mode);
 
  static char str[65536];
  char *string = &str[0];
  FILE *fp = fopen("/home/nector/ics2019/nemu/tools/gen-expr/input","r");
  assert(fp != NULL);
  while (!feof(fp)) {
      fgets(string,30,fp);
	  printf("%s",string);
  }
  char *arg = strtok(string,"$");
  arg = strtok(NULL,"$");
  bool success = true;
  uint32_t result = expr(arg,&success);
  fclose(fp);
  printf("%u\n",result);
  

  return 0;
}
