#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"
#include "stdint.h"

typedef struct watchpoint {
  int NO;
  bool work_state;
  char expression[32]; 
  uint32_t Old_Value;
  uint32_t New_Value;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */


} WP;

void init_wp_pool();

WP *new_wp();

void free_wp(WP *wp);

void delete_wp(int NO);

void set_wp(WP *wp, char *args);

void wp_display();

uint32_t wp_detect();
#endif
