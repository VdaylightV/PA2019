#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"
#include "stdint.h"

typedef struct watchpoint {
  int NO;
  bool work_state;
  char var_name[32]; 
  uint32_t Old_Value;
  uint32_t New_Value;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */


} WP;

#endif
