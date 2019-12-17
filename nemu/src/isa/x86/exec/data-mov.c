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
  
  rtl_pop(&id_dest->val);
  operand_write(id_dest, &id_dest->val);
  
  
  /*My code!!!
  rtl_pop(&id_src->val);
  operand_write(id_dest, &id_src->val);
  */

  //printf("HHHHHHHHHHHHHHHHHHH___%d___ HHHHHHHHHHHHHHHHH\n_", id_dest->reg);
  //printf("HHHHHHHHHHHHHHHHHHH___0x%x___ HHHHHHHHHHHHHHHHH\n_", id_dest->val);
 // printf("HHHHHHHHHHHHHHHHHHH___%d___ HHHHHHHHHHHHHHHHH\n_", id_dest->type);
 // printf("HHHHHHHHHHHHHHHHHHH___0x%x___ HHHHHHHHHHHHHHHHH\n_", cpu.ebx);

  print_asm_template1(pop);
}

make_EHelper(pusha) {
  
  rtl_lr(&s0, 4, 4);
  rtl_push(&cpu.eax);
  rtl_push(&cpu.ecx);
  rtl_push(&cpu.edx);
  rtl_push(&cpu.ebx);
  rtl_push(&s0);
  rtl_push(&cpu.ebp);
  rtl_push(&cpu.esi);
  rtl_push(&cpu.edi);
  
  
  /*My code!!!
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
  */

  print_asm("pusha");
}

make_EHelper(popa) {
  
  rtl_pop(&cpu.edi);
  rtl_pop(&cpu.esi);
  rtl_pop(&cpu.ebp);
  rtl_pop(&s0);
  rtl_pop(&cpu.ebx);
  rtl_pop(&cpu.edx);
  rtl_pop(&cpu.ecx);
  rtl_pop(&cpu.eax);
  
  
  /*My code!!!
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
  */

  print_asm("popa");
}

make_EHelper(leave) {
  
  rtl_sr(4, &cpu.ebp, 4);
  rtl_pop(&cpu.ebp);
  
  /*/My code!!!
  // cpu.esp = cpu.ebp;
  rtl_mv(&cpu.esp, &cpu.ebp);
  rtl_pop(&cpu.ebp);
  */
  // TODO();

  print_asm("leave");
}

make_EHelper(cltd) {
  if (decinfo.isa.is_operand_size_16) {
    cpu.gpr[R_DX]._16 = (cpu.gpr[R_AX]._16 & 0x8000)? 0xffff : 0;
    
    /* My code!!!
	  rtl_sext(&s0, &reg_l(R_EAX), 2);
	  rtl_shri(&reg_l(R_EDX), &s0, 16);
    */
/*	s0 = 15;
	rtl_shr(&cpu.edx, &cpu.eax, &s0);
*/
    //TODO();
  }
  else {
    cpu.gpr[R_EDX]._32 = (cpu.gpr[R_EAX]._32 & 0x80000000) ? 0xffffffff : 0;
    
    /*My code!!!
	  rtl_sari(&reg_l(R_EDX), &reg_l(R_EAX), 31);
    */
/*	s0 = 31;
	rtl_shr(&cpu.edx, &cpu.eax, &s0);
*/  //TODO();
  }

  print_asm(decinfo.isa.is_operand_size_16 ? "cwtl" : "cltd");
}

make_EHelper(cwtl) {
	
  if (decinfo.isa.is_operand_size_16) {
    
    rtl_lr(&s0, R_EAX, 1);
    s0 = (int32_t)(s0 << 24) >> 24;
    rtl_sr(R_EAX, &s0, 2);
    
/*	  if(((cpu.eax >> 15) & 1) == 1) {
	      cpu.eax = cpu.eax | 0xffff0000;
	  }
*/
    
    /*My code!!!
	  rtl_shli(&cpu.eax, &cpu.eax, 24);
	  rtl_sari(&cpu.eax, &cpu.eax, 8);
	  rtl_shri(&cpu.eax, &cpu.eax, 16);
    */
  //  TODO();
  }
  else {
    
    rtl_lr(&s0, R_EAX, 2);
    s0 = (int32_t)(s0 << 16) >> 16;
    rtl_sr(R_EAX, &s0, 4);
    
    
    /*My code!!!
	  rtl_sext(&cpu.eax, &cpu.eax, 2);
    */
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

make_EHelper(movs) {
  
  if(id_dest->width != 1) {
    id_dest->width = decinfo.isa.is_operand_size_16 ? 2 : 4;
  }
  s0 = cpu.esi;
//  rtl_lm(&cpu.edi, &cpu.esi, id_dest->width);
  rtl_lm(&s1, &s0, id_dest->width);
  s0 = cpu.edi;
  rtl_lm(&s0, &s1, id_dest->width);
//  rtl_addi(&cpu.edi, &cpu.edi, s0);  
//  rtl_addi(&cpu.esi, &cpu.esi, s0);  
  cpu.esi += id_dest->width;
  cpu.edi += id_dest->width;

  /*
  id_dest->width = decinfo.isa.is_operand_size_16 ? 2 : 4;
  rtl_lm(&cpu.edi, &cpu.esi, id_dest->width);
  s0 = id_dest->width;
//  rtl_add(&cpu.edi, &cpu.edi, &s0);  
//  rtl_add(&cpu.esi, &cpu.esi, &s0);  
  cpu.edi += s0;
  cpu.esi += s0;
  */
  print_asm_template2(movs);
}

make_EHelper(lea) {
  operand_write(id_dest, &id_src->addr);
  print_asm_template2(lea);
}
