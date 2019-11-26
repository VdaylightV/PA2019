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
  rtl_li(&s0, cpu.esp);
  rtl_push(&cpu.eax);
  rtl_push(&cpu.ecx);
  rtl_push(&cpu.edx);
  rtl_push(&cpu.ebx);
  rtl_push(&s0);
  rtl_push(&cpu.ebp);
  rtl_push(&cpu.esi);
  rtl_push(&cpu.edi);
  //TODO();

  print_asm("pusha");
}

make_EHelper(popa) {
  uint32_t throwaway;
  rtl_pop(&cpu.edi);
  rtl_pop(&cpu.esi);
  rtl_pop(&cpu.ebp);
  rtl_pop(&throwaway);
  rtl_pop(&cpu.ebx);
  rtl_pop(&cpu.edx);
  rtl_pop(&cpu.ecx);
  rtl_pop(&cpu.eax);
  //TODO();

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
	  rtl_sext(&s0, &reg_l(R_EAX), 2);
	  rtl_shri(&reg_l(R_EDX), &s0, 16);

/*	s0 = 15;
	rtl_shr(&cpu.edx, &cpu.eax, &s0);
*/
    //TODO();
  }
  else {
	  rtl_sari(&reg_l(R_EDX), &reg_l(R_EAX), 31);

/*	s0 = 31;
	rtl_shr(&cpu.edx, &cpu.eax, &s0);
*/  //TODO();
  }

  print_asm(decinfo.isa.is_operand_size_16 ? "cwtl" : "cltd");
}

make_EHelper(cwtl) {
	
  if (decinfo.isa.is_operand_size_16) {
/*	  if(((cpu.eax >> 15) & 1) == 1) {
	      cpu.eax = cpu.eax | 0xffff0000;
	  }
*/
	  rtl_shli(&cpu.eax, &cpu.eax, 24);
	  rtl_sari(&cpu.eax, &cpu.eax, 8);
	  rtl_shri(&cpu.eax, &cpu.eax, 16);
  //  TODO();
  }
  else {
	  rtl_sext(&cpu.eax, &cpu.eax, 2);
  //  TODO();
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
