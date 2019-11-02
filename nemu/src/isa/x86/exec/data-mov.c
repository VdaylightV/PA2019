#include "cpu/exec.h"

make_EHelper(mov) {
  operand_write(id_dest, &id_src->val);
  print_asm_template2(mov);
}

make_EHelper(push) {
  rtl_push(&id_dest->val);

//  printf("!!!!!!!!!!!!!!!!!!!The value to be pushed: %x\n", id_src->val);
//   print_asm("push %x", id_src->val);

  print_asm_template1(push);
}

make_EHelper(pop) {
  //printf("HHHHHHHHHHHHHHHHHHH___%d___ HHHHHHHHHHHHHHHHH\n_", id_dest->reg);
  rtl_pop(&id_src->val);
  operand_write(id_dest, &id_src->val);
  //printf("HHHHHHHHHHHHHHHHHHH___0x%x___ HHHHHHHHHHHHHHHHH\n_", id_dest->val);
 // printf("HHHHHHHHHHHHHHHHHHH___%d___ HHHHHHHHHHHHHHHHH\n_", id_dest->type);
 // printf("HHHHHHHHHHHHHHHHHHH___0x%x___ HHHHHHHHHHHHHHHHH\n_", cpu.ebx);

  print_asm_template1(pop);
}

make_EHelper(pusha) {
  TODO();

  print_asm("pusha");
}

make_EHelper(popa) {
  TODO();

  print_asm("popa");
}

make_EHelper(leave) {
 // cpu.esp = cpu.ebp;
  rtl_mv(&cpu.esp, &cpu.ebp);
  rtl_pop(&cpu.ebp);
  // TODO();

  print_asm("leave");
}

make_EHelper(cltd) {
  if (decinfo.isa.is_operand_size_16) {
	s0 = 15;
	rtl_shr(&cpu.edx, &cpu.eax, &s0);

    //TODO();
  }
  else {
	s0 = 31;
	rtl_shr(&cpu.edx, &cpu.eax, &s0);
    //TODO();
  }

  print_asm(decinfo.isa.is_operand_size_16 ? "cwtl" : "cltd");
}

make_EHelper(cwtl) {
  if (decinfo.isa.is_operand_size_16) {
    TODO();
  }
  else {
    TODO();
  }

  print_asm(decinfo.isa.is_operand_size_16 ? "cbtw" : "cwtl");
}

make_EHelper(movsx) {
  id_dest->width = decinfo.isa.is_operand_size_16 ? 2 : 4;
  rtl_sext(&s0, &id_src->val, id_src->width);
  operand_write(id_dest, &s0);
  print_asm_template2(movsx);
}

make_EHelper(movzx) {
  id_dest->width = decinfo.isa.is_operand_size_16 ? 2 : 4;
  operand_write(id_dest, &id_src->val);
  print_asm_template2(movzx);
}

make_EHelper(lea) {
  operand_write(id_dest, &id_src->addr);
  print_asm_template2(lea);
}
