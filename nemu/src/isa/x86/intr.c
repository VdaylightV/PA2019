#include "rtl/rtl.h"

void raise_intr(uint32_t NO, vaddr_t ret_addr) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * That is, use ``NO'' to index the IDT.
   */
   rtl_push(&cpu.eflags.value);
   rtl_push(&cpu.cs);
   //rtl_push(&cpu.pc);
   rtl_push(&ret_addr);

   uint32_t addr;
   uint32_t offset1;
   uint32_t offset2;

  /*
   s1 = vaddr_read(s0 + NO * 8, 4);
   s2 = vaddr_read(s0 + NO * 8 + 4, 4);
  */

   offset1 = vaddr_read(0x134220, 4);
   offset2 = vaddr_read(0x134220 + 4, 4);
   
   addr = ((offset2 & 0xffff0000) + (offset1 & 0x0000ffff));
 // printf("address head:0x%x\n", cpu.idtr.base);
   printf("NO:0x%x\n", NO);
  // printf("addr offset1:0x%x\n", cpu.idtr.base + NO * 8);
  // printf("addr offset2:0x%x\n", cpu.idtr.base + NO * 8 + 4);
   printf("offset1:0x%x\n", offset1);
   printf("offset2:0x%x\n", offset2);
   printf("address:0x%x\n", addr);
   
   rtl_j(addr);
  

}

bool isa_query_intr(void) {
  return false;
}
