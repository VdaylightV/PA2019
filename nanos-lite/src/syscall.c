#include "common.h"
#include "syscall.h"
#include "klib.h"

int sys_write(_Context *c) {
  uintptr_t temp[3];
  temp[0] = c->GPR2;
  temp[1] = c->GPR3;
  temp[2] = c->GPR4;

  if(temp[0] == 1 || temp[0] == 2) {
    char *buf = (char*) temp[1];
    for(int i = 0; i < temp[2]; i ++) {
      _putc(buf[i]);
    }
  }

   return temp[2]; 
}

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  
  switch (a[0]) {
	case SYS_yield: {_yield(); c->GPRx = 0; break;}
  case SYS_exit: {_halt(c->GPR2); break;}
  case SYS_write: { c->GPRx = sys_write(c); break;}
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}
