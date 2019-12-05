#include <am.h>
#include <x86.h>
#include "klib.h"

static _Context* (*user_handler)(_Event, _Context*) = NULL;

void __am_irq0();
void __am_vecsys();
void __am_vectrap();
void __am_vecnull();

_Context* __am_irq_handle(_Context *c) {
  _Context *next = c;
  /*
  printf("eax:0x%08x\n", c->eax);
  printf("ecx:0x%08x\n", c->ecx);
  printf("edx:0x%08x\n", c->edx);
  printf("ebx:0x%08x\n", c->ebx);
  printf("esp:0x%08x\n", c->esp);
  printf("ebp:0x%08x\n", c->ebp);
  printf("esi:0x%08x\n", c->esi);
  printf("edi:0x%08x\n", c->edi);
  printf("eflags:0x%08x\n", c->eflags);
  printf("cs:0x%08x\n", c->cs);
  printf("pc:0x%08x\n", c->pc);
  */
  if (user_handler) {
    _Event ev = {0};
    switch (c->irq) {
      case 0x81: {ev.event = _EVENT_YIELD; /*printf("???????????????%d\n",ev.event);*/ break;}
      default:{/*printf("############%d\n", c->irq);*/ev.event = _EVENT_ERROR; break;}
    }

    next = user_handler(ev, c);
    if (next == NULL) {
      next = c;
    }
  }

  return next;
}

int _cte_init(_Context*(*handler)(_Event, _Context*)) {
  static GateDesc idt[NR_IRQ];
  //printf("??????????????????????????\n?");

  // initialize IDT
  for (unsigned int i = 0; i < NR_IRQ; i ++) {
    idt[i] = GATE(STS_TG32, KSEL(SEG_KCODE), __am_vecnull, DPL_KERN);
  }

  // ----------------------- interrupts ----------------------------
  idt[32]   = GATE(STS_IG32, KSEL(SEG_KCODE), __am_irq0,   DPL_KERN);
  // ---------------------- system call ----------------------------
  //printf("**************************\n");
  idt[0x80] = GATE(STS_TG32, KSEL(SEG_KCODE), __am_vecsys, DPL_USER);
  //printf("$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
  idt[0x81] = GATE(STS_TG32, KSEL(SEG_KCODE), __am_vectrap, DPL_KERN);

  set_idt(idt, sizeof(idt));

  // register event handler
  user_handler = handler;

  return 0;
}

_Context *_kcontext(_Area stack, void (*entry)(void *), void *arg) {
  return NULL;
}

void _yield() {
  //printf("What?***************************************************************************************************************************************************************************\n");
  asm volatile("int $0x81");
}

int _intr_read() {
  return 0;
}

void _intr_write(int enable) {
}
