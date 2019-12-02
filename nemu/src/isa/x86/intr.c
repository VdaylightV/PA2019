#include "rtl/rtl.h"

void raise_intr(uint32_t NO, vaddr_t ret_addr) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * That is, use ``NO'' to index the IDT.
   */
   rtl_push(&cpu.eflags.value);
   rtl_push(&cpu.cs);
   //rtl_push(&cpu.pc);
   rtl_push(&ret_addr);

   s0 = cpu.idtr.base;

   s1 = vaddr_read(s0 + NO * 8, 4);
   s2 = vaddr_read(s0 + NO * 8 + 4, 4);

   s0 = (((s2 & 0x0000ffff) << 16) | (s1 & 0x0000ffff));
   
   rtl_j(s0);

}

bool isa_query_intr(void) {
  return false;
}
