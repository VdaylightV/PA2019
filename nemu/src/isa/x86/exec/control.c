#include "cpu/exec.h"
#include "cc.h"

make_EHelper(jmp) {
  // the target address is calculated at the decode stage
  rtl_j(decinfo.jmp_pc);

  print_asm("jmp %x", decinfo.jmp_pc);
}

make_EHelper(jcc) {
  // the target address is calculated at the decode stage
  uint32_t cc = decinfo.opcode & 0xf;
  rtl_setcc(&s0, cc);
  rtl_li(&s1, 0);
  rtl_jrelop(RELOP_NE, &s0, &s1, decinfo.jmp_pc);

  print_asm("j%s %x", get_cc_name(cc), decinfo.jmp_pc);
}

make_EHelper(jmp_rm) {
  rtl_j(id_dest->val);

  print_asm("jmp *%s", id_dest->str);
}

make_EHelper(call) {
  s0 = decinfo.seq_pc;
  rtl_push(&s0);
  rtl_j(decinfo.jmp_pc);
  /* rtl_push(&cpu.pc);
//  printf("@@@@@@@@@@@@____%x____@@@@@@@@@@@@\n", decinfo.seq_pc);
  // the target address is calculated at the decode stage
  */// TODO();
  print_asm("call %x", decinfo.jmp_pc);
}

make_EHelper(ret) {
  
  rtl_pop(&s0);
  rtl_j(s0); 
  
  
  /*My code !!! 
  rtl_pop(&decinfo.jmp_pc);
  rtl_j(decinfo.jmp_pc);
  */
  //rtl_mv(&cpu.esp, &cpu.ebp);
  /* 
  rtl_lm(&s0, &cpu.esp, 4);
  rtl_pop(&s1);
  */
  //rtl_lm(&s0, &cpu.esp, 4);
  //rtl_j(s0);
  //decinfo.is_jmp = true;

   //TODO();

  print_asm("ret");
}

make_EHelper(ret_imm) {
  TODO();

  print_asm("ret %s", id_dest->str);
}

make_EHelper(call_rm) {
  
  s0 = decinfo.seq_pc;
  rtl_push(&s0);
  rtl_j(id_dest->val);
  
  //TODO();
  
  /*My code!!!
  rtl_push(&decinfo.seq_pc);
  rtl_jr(&id_dest->val);
  */
  print_asm("call *%s", id_dest->str);
}
