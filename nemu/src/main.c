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
 
  static char str[300];
//  char *string = &str[0];
  FILE *fp = fopen("/home/nector/ics2019/nemu/tools/gen-expr/input","r");
  assert(fp != NULL);

//  while (*fp != '\0') {
    while ( !feof(fp)) {
      //fgets(str,500,fp);
//	  fscanf(fp,"%s",&str[0]);
	  int len;
	  len = strlen(str);
	  str[len-1] = '\0';
	  printf("%s \n", str);		  

 // int j = 20;
	  char *args = strtok(str, "$");
	  while (*args != ' ') {
      args ++;
  }
/*  printf("%c\n",*args);
  while ( j > 0 ) {
      args++; //= strtok(NULL,"$"); 
	  printf("%c\n",*args);
	  j--;
  }
  assert(args != NULL);
  args = strtok(" ","$");
  printf("%c\n",*args);
*/
  /*
  char *arg = strtok(string,"$");
  assert(arg != NULL);
  arg = strtok(NULL,"$");
*/
	 bool success = true;
	 uint32_t result = expr(args,&success);
	 printf("%u\n",result);
  
  }

	 fclose(fp);
  
/*
  while(fscanf(fp, "%[^\n]%c",&str,&c) != EOF) {
      if(str!="")
	  {
		  fputs(str,stdout);
		  printf("\n");
		  memset(str,0,sizeof(char));
	  }
	  else
		  printf("error:no content\n");
  }
*/
//  fclose(fp);
  return 0;
}
