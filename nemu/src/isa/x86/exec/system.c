#include "cpu/exec.h"

void raise_intr(uint32_t, vaddr_t);

make_EHelper(lidt) {
  //TODO();
  /*
  s0 = id_dest->addr;
  if(id_dest->width == 2) {
      cpu.idtr.base = vaddr_read(s0 + 2, 3);
      cpu.idtr.limit = vaddr_read(s0, 2);
  }
  else {
      cpu.idtr.base = vaddr_read(s0 + 2, 4);
      cpu.idtr.limit = vaddr_read(s0, 2);
  }
  */
  /*
  rtl_li(&s0, id_dest->addr);
  rtl_li(&cpu.idtr.limit, vaddr_read(s0, 2));
  rtl_li(&cpu.idtr.base, vaddr_read(s0+2,4));
  */

  rtl_lm((uint32_t*)&cpu.idtr.limit, &id_dest->addr, 2);
  printf("id_dest->addr:0x%x\n", id_dest->addr);
  printf("limit:0x%x\n", cpu.idtr.limit);
  rtl_addi(&s0, &id_dest->addr, 2);
  printf("id_dest->addr + 2:0x%x\n", s0);
  rtl_lm(&cpu.idtr.base, &s0, 4);
  printf("base:0x%x\n", cpu.idtr.base);
  print_asm_template1(lidt);
}

make_EHelper(mov_r2cr) {
  TODO();

  print_asm("movl %%%s,%%cr%d", reg_name(id_src->reg, 4), id_dest->reg);
}

make_EHelper(mov_cr2r) {
  TODO();

  print_asm("movl %%cr%d,%%%s", id_src->reg, reg_name(id_dest->reg, 4));

  difftest_skip_ref();
}

make_EHelper(int) {
	raise_intr(id_dest->val, decinfo.seq_pc);
  //TODO();

  print_asm("int %s", id_dest->str);

  difftest_skip_dut(1, 2);
}

make_EHelper(iret) {
  
  rtl_pop(&s0);
  rtl_pop(&cpu.cs);
  rtl_pop(&cpu.eflags.value);
  rtl_j(s0);

/*
  rtl_pop(&decinfo.jmp_pc);
  rtl_j(decinfo.jmp_pc);
  rtl_pop(&cpu.cs);
  rtl_pop(&cpu.eflags.value);
*/

  //TODO();

  print_asm("iret");
}

uint32_t pio_read_l(ioaddr_t);
uint32_t pio_read_w(ioaddr_t);
uint32_t pio_read_b(ioaddr_t);
void pio_write_l(ioaddr_t, uint32_t);
void pio_write_w(ioaddr_t, uint32_t);
void pio_write_b(ioaddr_t, uint32_t);

make_EHelper(in) {

	switch(id_src->width) {
	    case 1: { s0 = pio_read_b(id_src->val); break; }
	    case 2: { s0 = pio_read_w(id_src->val); break; }
	    case 4: { s0 = pio_read_l(id_src->val); break; }
		default: assert(0);
	}

    operand_write(id_dest, &s0);
//  TODO();

  print_asm_template2(in);
}

make_EHelper(out) {

    s0 = id_src->val;

	switch(id_src->width) {
	    case 1: { pio_write_b(id_dest->val, s0); break; }
	    case 2: { pio_write_w(id_dest->val, s0); break; }
	    case 4: { pio_write_l(id_dest->val, s0); break; }
		default: assert(0);
	}
//  TODO();

  print_asm_template2(out);
}
