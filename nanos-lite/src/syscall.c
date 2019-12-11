#include "common.h"
#include "syscall.h"
#include "klib.h"

int fs_open(const char *pathname);
size_t fs_read(int fd, void *buf, size_t count);
int fs_close(int fd);
size_t fs_lseek(int fd, size_t offset, int whence);
size_t fs_write(int fd, const void *buf, size_t count);

size_t ramdisk_read(void *buf, size_t offset, size_t len);

int sys_yield(_Context *c) {
//void sys_yield(_Context *c) {
  _yield();
//  c->GPRx = 0;
  return 0;
}

void sys_exit(_Context *c) {
  _halt(c->GPR2);
}


//void sys_open(_Context *c) {
int sys_open(_Context *c) {
  //c->GPRx = fs_open((char*)c->GPR2);
  
  uintptr_t temp[1];
  temp[0] = c->GPR2;
  int descriptor = fs_open((const char*)temp[0]);
  return descriptor;
  
}

int sys_lseek(_Context *c) {
//void sys_lseek(_Context *c) {
  
  uintptr_t temp[3];
  temp[0] = c->GPR2;
  temp[1] = c->GPR3;
  temp[2] = c->GPR4;
  size_t current_offset = fs_lseek(temp[0], temp[1], temp[2]);
  return current_offset;
  
 //c->GPRx = fs_lseek(c->GPR2, c->GPR3, c->GPR4);
}

//void sys_read(_Context *c) {
int sys_read(_Context *c) {
  
  uintptr_t temp[3];
  temp[0] = c->GPR2;
  temp[1] = c->GPR3;
  temp[2] = c->GPR4;
  size_t len = fs_read(temp[0], (void*)temp[1], temp[2]);
  return len;
  
 //c->GPRx = fs_read(c->GPR2, (char*)c->GPR3, c->GPR4);
}

int sys_close(_Context *c) {
//void sys_close(_Context *c) {
  
  uintptr_t temp[1];
  temp[0] = c->GPR2;
  int code = fs_close(temp[0]);
  return code;
  
  // c->GPRx = fs_close(c->GPR2);
}

//void sys_write(_Context *c) {
int sys_write(_Context *c) {
  
  uintptr_t temp[3];
  temp[0] = c->GPR2;
  temp[1] = c->GPR3;
  temp[2] = c->GPR4;

  int len = fs_write(temp[0], (void*)temp[1], temp[2]);
  
  //Log("abcdefghijklmnopqrstuvwxyz");
  
  if(temp[0] == 1 || temp[0] == 2) {
    char *buf = (char*) temp[1];
    for(int i = 0; i < temp[2]; i ++) {
      _putc(buf[i]);
    }
  }
  

   return len; 

 //c->GPRx = fs_write(c->GPR2, (char*)c->GPR3, c->GPR4);
}

//void sys_brk(_Context *c) {
int sys_brk(_Context *c) {
  
    return 0;
   	// c->GPRx = 0;
}

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  
  switch (a[0]) {
	case SYS_yield: { c->GPRx = sys_yield(c); break;}
    case SYS_exit: { sys_exit(c); break;}
    case SYS_write: { c->GPRx = sys_write(c); break;}
    case SYS_brk: { c->GPRx = sys_brk(c); break;}
    case SYS_open: { c->GPRx = sys_open(c); break;}
	case SYS_read: { c->GPRx = sys_read(c); break;}
    case SYS_close: { c->GPRx = sys_close(c); break;}
    case SYS_lseek: { c->GPRx = sys_lseek(c); break;}
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}
