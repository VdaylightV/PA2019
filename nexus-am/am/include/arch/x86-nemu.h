#ifndef __ARCH_H__
#define __ARCH_H__

struct _Context {
  //uintptr_t esi, ebx, eax, eip, edx, eflags, ecx, cs, esp, edi, ebp;
  uintptr_t esi, edi, ebp, esp, ebx, ecx, edx, eax;
  int irq;
  uintptr_t pc, cs, eflags; 
  struct _AddressSpace *as;
};

#define GPR1 eax
#define GPR2 eip
#define GPR3 eip
#define GPR4 eip
#define GPRx eip

#endif
