#include "proc.h"
#include <elf.h>

#ifdef __ISA_AM_NATIVE__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

size_t ramdisk_read(void *buf, size_t offset, size_t len);

static uintptr_t loader(PCB *pcb, const char *filename) {
  
  //TODO();
  int i;
  char buf[65535] = "";
  char* buf_head = &buf[0];

  ramdisk_read(buf_head, 0x001000, 0x03a43);
  memcpy((uintptr_t*)0x03001000, buf_head, 0x03a43);
  memset((uintptr_t*)(0x03001000+0x03a43), 0, 1);
 
  i = 0; 
  while(buf[i] != '\0') {
      buf[i] = '\0';
	  i ++;

	  if (i > 0xfffff) {
	      assert(0);
	  }
  }
   
  ramdisk_read(buf_head, 0x005000, 0x01918);
  memcpy((uintptr_t*)0x03005000, buf_head, 0x01918);
  memset((uintptr_t*)(0x03005000+0x01918), 0, 1);

  i = 0; 
  while(buf[i] != '\0') {
      buf[i] = '\0';
	  i ++;
  }
   
  ramdisk_read(buf_head, 0x007000, 0x00868);
  memcpy((uintptr_t*)0x03008000, buf_head, 0x008d8);
  memset((uintptr_t*)(0x03008000+0x00868), 0, 0x00071);

  return 0;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %x", entry);
  ((void(*)())entry) ();
}

void context_kload(PCB *pcb, void *entry) {
  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _kcontext(stack, entry, NULL);
}

void context_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);

  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _ucontext(&pcb->as, stack, stack, (void *)entry, NULL);
}
