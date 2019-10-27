#include "cpu/exec.h"
#include "cc.h"

make_EHelper(test) {
 printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
 rtl_and(&s1, &id_src->val, &id_dest->val);
 printf("HHHHHHHHHH:_________%u__________:HHHHHHHHHHHHH\n",s1);
 if (s1 == 0) {
    cpu.eflags.ZF = 1;
 }
 else {
    cpu.eflags.ZF = 0;
 }
 // TODO();

  print_asm_template2(test);
}

make_EHelper(and) {
  
  id_dest->width = decinfo.isa.is_operand_size_16 ? 2 : 4;
  rtl_sext(&s1, &id_src->val, id_src->width);
  
  /*
  int32_t temp = (int32_t)id_src->val;
  temp = (temp << 24) >> 24;
  uint32_t rs = (uint32_t)temp;
  printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH%u\n",rs);
  */
  rtl_and(&s0, &id_dest->val, &s1);

  operand_write(id_dest, &s0);
  //TODO();

  print_asm_template2(and);
}

make_EHelper(xor) {
  rtl_xor(&s0, &id_dest->val, &id_src->val);
  
  operand_write(id_dest, &s0);
   //TODO();

  print_asm_template2(xor);
}

make_EHelper(or) {
  TODO();

  print_asm_template2(or);
}

make_EHelper(sar) {
  TODO();
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(sar);
}

make_EHelper(shl) {
  TODO();
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(shl);
}

make_EHelper(shr) {
  TODO();
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(shr);
}

make_EHelper(setcc) {
  uint32_t cc = decinfo.opcode & 0xf;

  rtl_setcc(&s0, cc);
  operand_write(id_dest, &s0);

  print_asm("set%s %s", get_cc_name(cc), id_dest->str);
}

make_EHelper(not) {
  TODO();

  print_asm_template1(not);
}
